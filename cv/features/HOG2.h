#ifndef HOG2_H
#define HOG2_H



#include "../../Assertions.h"
#include "../ImageChannel.h"
#include "../ImagePoint.h"
#include "../Derivative.h"

#include "../../math/statistics/Histogram.h"

#include "../Kernel.h"
#include "../KernelFactory.h"

#include "../../geo/Size2.h"
#include "../../geo/Point2.h"


namespace K {




	/**
	 * calculate the histogram-of-gradients at a given
	 * location using a provided region (size)
	 *
	 * // http://stackoverflow.com/questions/32417531/hog-what-is-done-in-the-contrast-normalization-step
	 * // http://www.geocities.ws/talh_davidc/#cst_extract
	 *
	 * - no smoothing beforehand!
	 * - [0:180] degree region!
	 *   - a 270 degree gradient is the same as a 90 degree gradient -> modulo
	 *
	 */
	class HOG2 {

	private:

		struct HOGGradient {
			float magnitude;
			float direction;		// in radians [0:2pi] 0 = left, pi/2 = up
		};



		// get half the given value. rounded down!
		static inline int half(const int i) {return i/2;}

	public:

		enum Pattern {
			RECTANGULAR,
			CIRCULAR,
		};

		struct CellPoint : public ImagePoint {
			float impact;			// from gaussian, to downweight edge-pixels
			CellPoint(const int x, const int y, const float impact) : ImagePoint(x,y), impact(impact) {;}
		};

		struct Contribution {
			int bin;
			float weight;
			Contribution() : bin(0), weight(0) {;}
			Contribution(int bin, float weight) : bin(bin), weight(weight) {;}
		};

		struct Contributions {
			Contribution c1;
			Contribution c2;
			Contributions(const Contribution c1, const Contribution c2) : c1(c1), c2(c2) {;}
		};

		/** helper class to describe the feature-area based on the HOG settings */
		struct Area {

			// upper left coordinate for the area-of-interest
			int sx;
			int sy;

			// first [upper left] block's center
			int cx;
			int cy;

			// number of x and y blocks within the window
			int wx;
			int wy;

			const Size2i blockStride;

			Area(const Point2i pos, const Size2i blockSize, const Size2i winSize, const Size2i blockStride) : blockStride(blockStride) {

				// upper left coordinate for the area-of-interest
				sx = pos.x - half(winSize.w);
				sy = pos.y - half(winSize.h);

				// first [upper left] block's center
				cx = sx + half(blockSize.w);
				cy = sy + half(blockSize.h);

				// number of x and y blocks within the window
				wx = ((winSize.w - blockSize.w) / blockStride.w) + 1;
				wy = ((winSize.h - blockSize.h) / blockStride.h) + 1;

			}

			/** get the center for the nx-th/ny-th block */
			Point2i getBlockCenter(const int nx, const int ny) const {
				return Point2i(
					cx + nx*blockStride.w,
					cy + ny*blockStride.h
				);
			}

		};

		struct Vector : public std::vector<float> {

			Vector() {
				;
			}

			Vector(const size_t size) {
				this->reserve(size);
			}

			/** ensure the vector has a length of 1 */
			void normalize() {
				float length = 0;
				for (float  f : *this) {length += f*f;}
				length += 0.2f; // this constant serves two purposes: prevent length = 0, and prevent near-0 vectors from getting too long
				length = std::sqrt(length);
				for (float& f : *this) {f /= length;}
			}

			float length() const {
				float length = 0;
				for (float  f : *this) {length += f*f;}
				return std::sqrt(length);
			}

			float distance(const Vector& o) const {
				float sum = 0;
				for (size_t i = 0; i < size(); ++i) {
					const float d = (*this)[i] - o[i];
					sum += d*d;
				}
				return std::sqrt(sum);
			}

		};

	private:

		/** the size for each cell [cell is the smallest element] */
		const Size2i cellSize;

		/** the number of bins to use within each cell */
		const int bins;

		/** number of degrees per bin */
		const float degPerBin;

		/** currently we pre-calculate everything at pixel-level [highest accuracy] */
		const int stride = 1;


		/** the size for each block [containing several cells]. must be a multiple of the cellSize */
		const Size2i blockSize;


		/** number of float-values per cell */
		const int valuesPerCell;

		/** number of float-values per block */
		const int valuesPerBlock;


		/** sigma to (slightly) downweight edge pixels */
		const float sigma = 5.0f;


		/** downweight each block's edge pixels [more importance to the center] */
		K::Kernel gauss;

		/** histogram for each cell */
		DataMatrix<Vector> cells;

		/** histogram for each block [multiple cells] */
		DataMatrix<Vector> blocks;


	public:

		/** ctor */
		HOG2(const ImageChannel& img, const Size2i cellSize = Size2i(8,8), const int bins = 9, const Size2i blockSize = Size2i(16,16)) :
			cellSize(cellSize), bins(bins), degPerBin(180.0f / (float)bins), blockSize(blockSize),
			valuesPerCell(bins),
			valuesPerBlock(valuesPerCell*(blockSize.w/cellSize.w)*(blockSize.h/cellSize.h)) {

			if (blockSize.w != blockSize.h) {throw Exception("currently, only square blocks are supported");}

			// perform some sanity checks
			if (blockSize.w % cellSize.w != 0) {throw Exception("blockSize must be a multiple of cellSize");}
			if (blockSize.h % cellSize.h != 0) {throw Exception("blockSize must be a multiple of cellSize");}

			// TODO
			gauss = K::KernelFactory::gauss2D(0.5, cellSize.w);

			// TODO: searching stride? (currently 1px, but requires many [unnecessary] calculations)

			precalc(img);

		}

		/** get the histogram for the cell around [=centered at] (x,y) */
		const Vector& getCell(const int x, const int y) const {
			//if (x % stride != 0) {throw Exception("x-coordinate must be a multiple of the stride-size");}
			//if (y % stride != 0) {throw Exception("y-coordinate must be a multiple of the stride-size");}
			if ((x < cellSize.w / 2) || (y < cellSize.h / 2)) {throw Exception("block position out of bounds");}
			return cells.getConstRef(x/stride, y/stride);
		}

		/** get the historgram for the block around [=centered at] (x,y) */
		const Vector& getBlock(const int x, const int y) const {
			//if (x % stride != 0) {throw Exception("x-coordinate must be a multiple of the stride-size");}
			//if (y % stride != 0) {throw Exception("y-coordinate must be a multiple of the stride-size");}
			if ((x < blockSize.w / 2) || (y < blockSize.h / 2)) {throw Exception("window position out of bounds");}
			return blocks.getConstRef(x/stride, y/stride);
		}



		/** get a feature-vector for the given location (x,y) = center and size(w,h) */
		Vector getFeature(const Point2i pos, const Size2i winSize, const Size2i blockStride = Size2i(8,8)) const {

			//const int x = pos.x;
			//const int y = pos.y;

			const int w = winSize.w;
			const int h = winSize.h;

			// sanity checks
			//if (x % stride != 0)	{throw Exception("x-coordinate must be a multiple of the stride-size");}
			//if (y % stride != 0)	{throw Exception("y-coordinate must be a multiple of the stride-size");}

			if (w % cellSize.w != 0)	{throw Exception("window-width must be a multiple of the cell-width");}
			if (h % cellSize.h != 0)	{throw Exception("window-height must be a multiple of the cell-height");}

			if ((winSize.w - blockSize.w) % blockStride.w != 0) {throw Exception("err");}
			if ((winSize.h - blockSize.h) % blockStride.h != 0) {throw Exception("err");}

			//if (windowSize != 2*blockSize) {throw Exception("not yet supported!");}

			const Area a = Area(pos, blockSize, winSize, blockStride);

			const size_t reserve = a.wx*a.wy*valuesPerBlock;

			//Vector feature(reserve);
			Vector feature;
			feature.resize(reserve);
			float* data = feature.data();

			for (int y = 0; y < a.wy; ++y) {
				for (int x = 0; x < a.wx; ++x) {

					const Point2i pt = a.getBlockCenter(x, y);

					const Vector& block = getBlock(pt.x, pt.y);
					_assertNot0(block.size(), "invalid number of values in window detected");

					//feature.insert(feature.end(), block.begin(), block.end());
					memcpy(data, block.data(), block.size()*sizeof(float));
					data += block.size();

				}
			}

			_assertEqual(reserve, feature.size(), "invalid feature size");

			return feature;

		}


	public:

		// FOR TESTING

		/** convert from degress to bin number [float!] */
		inline float degToBin(const float deg) const {

			// sanity check
			if (deg < 0)	{throw Exception("degrees out of bounds");}
			if (deg > 360)	{throw Exception("degrees out of bounds");}

			return deg / degPerBin;

		}



		/** convert orientation + magnitude to a bin-contribution */
		Contributions getContribution(const float deg, const float mag) const {
			const float bin = degToBin(deg);
			Contribution c1, c2;
			c1.bin = (int) std::floor(bin);
			c2.bin = (int) std::ceil(bin);
			const float alpha = (bin - (float)c1.bin);
			c1.bin %= bins;
			c2.bin %= bins;
			c1.weight = mag * (1.0f - alpha);
			c2.weight = mag * (alpha);
			return Contributions(c1,c2);
		}


	private:

		inline float atan360(const float dy, const float dx) const {
			const float rad = std::atan2(dy, dx);
			return (rad >= 0.0) ? (rad) : (2.0f*(float)M_PI+rad);
		}

		/** perform one-time calculations for fast lookups */
		void precalc(const ImageChannel& img) {
			buildCells(img);
			buildBlocks(img);
		}

		/**
		 * step1)
		 * calculate HOG cells [usually 8x8] around each "pixel" of the input image
		 * TODO: do not calculate for each pixel [++i] but for [i+=stride]
		 * that will be used during the matching phase. this is less accurate but faster
		 */
		void buildCells(const ImageChannel& img) {

			const int w = img.getWidth();
			const int h = img.getHeight();

			// number of blocks to calculate
			const int nx = img.getWidth() / stride;
			const int ny = img.getHeight() / stride;

			// get derivative images (x and y)
			const K::ImageChannel imgX = Derivative::getXcen(img);		// [-1: 0: +1]
			const K::ImageChannel imgY = Derivative::getYcen(img);		// [-1: 0: +1]

			// buffer containing HOG-Block-Histogram for every stride-th-pixel within the image
			cells = DataMatrix<Vector>(nx, ny);

			// list of all pixels that belong to a HOG-window (centered at 0,0)
			const std::vector<CellPoint> region = getCellPoints(Pattern::RECTANGULAR);

			// border to skip [half block size]
			const int w2 = half(cellSize.w);
			const int h2 = half(cellSize.h);

			// build HOG-Histogram for each block centered at (x,y) with stride-th increment
			for (int y = h2; y <= h-h2; y += stride) {

				#pragma omp parallel for
				for (int x = w2; x <= w-w2; x += stride) {
					cells.set(x/stride, y/stride, getHistogram(imgX, imgY, x,y, region));
				}

			}

		}

		/**
		 * step2)
		 * calculate HOG blocks [=several cells] [usually 16x16 (or 2x2 cells)] around each "pixel" of the input image
		 */
		void buildBlocks(const ImageChannel& img) {

			//if (windowSize != 2*blockSize) {throw Exception("not yet supported!");}

			const int w = img.getWidth();
			const int h = img.getHeight();

			// number of windows to calculate
			const int nx = img.getWidth() / stride;
			const int ny = img.getHeight() / stride;

			// buffer containing HOG-Window-Vector for every stride-th-pixel within the image
			blocks = DataMatrix<Vector>(nx, ny);

			const int bsw2 = half(blockSize.w);
			const int bsh2 = half(blockSize.h);

			// build combined/normalized Histogram for each Window centered at (x,y)
			for (int y = bsh2; y <= h-bsh2; y += stride) {

				#pragma omp parallel for
				for (int x = bsw2; x <= w-bsw2; x += stride) {

					// upper left coordinate for the area-of-interest
					const int sx = x - half(blockSize.w);
					const int sy = y - half(blockSize.h);

					// first block's center
					const int cx = sx + half(cellSize.w);
					const int cy = sy + half(cellSize.h);

					// number of cells within each block
					const int cellsX = blockSize.w / cellSize.w;
					const int cellsY = blockSize.h / cellSize.h;

					// build the block
					const size_t reserve = cellsX*cellsY*bins;
					//Vector block(reserve);
					Vector block;
					block.resize(reserve);
					float* data = block.data();

					// fetch each cell that belongs to the block
					for (int y1 = 0; y1 < cellsY; ++y1) {
						for (int x1 = 0; x1 < cellsX; ++x1) {

							const int xx = cx + x1*cellSize.w;
							const int yy = cy + y1*cellSize.h;

							const Vector& cell = getCell(xx, yy);
							//block.insert(block.end(), cell.begin(), cell.end());
							memcpy(data, cell.data(), cell.size()*sizeof(float));
							data += cell.size();

						}
					}

					_assertEqual(reserve, block.size(), "invalid number of entries in block");

					// normalize the window
					block.normalize();

					// store
					blocks.set(x/stride, y/stride, block);

				}
			}

		}

//		/** convert gradients to histogram */
//		Vector getHistogram(const std::vector<HOGGradient>& gradients) {

//			Vector res(bins);
//			res.resize(bins);

//			for (const HOGGradient& hg : gradients) {

//				const float deg = hg.direction * 180.0f / (float)M_PI;
//				const Contributions c = getContribution(deg, hg.magnitude);

//				if (1 == 1) {
//					res[c.c1.bin] += c.c1.weight;	// split contribution
//					res[c.c2.bin] += c.c2.weight;
//				} else {
//					res[c.c1.bin] += c.c1.weight;	// both to the same bin
//					res[c.c1.bin] += c.c2.weight;	// both to the same bin
//				}

//			}

//			return res;

//		}



//		/** get all individual gradients at the given location */
//		std::vector<HOGGradient> getGradients(const K::ImageChannel& imgX, const K::ImageChannel& imgY, const int x, const int y, const std::vector<ImagePoint>& region) const {

//			std::vector<HOGGradient> gradients(bins);

//			for (size_t i = 0; i < region.size(); ++i) {

//				const ImagePoint p = region[i];

//				// point within the image
//				const int x1 = x+p.x;
//				const int y1 = y+p.y;

//				// clamp
//				if (x1 < 0 || x1 >= imgX.getWidth())	{continue;}
//				if (y1 < 0 || y1 >= imgX.getHeight())	{continue;}

//				// calculate the centered derivatives
//				const auto dx = imgX.get(x1, y1);	// gradient's magnitude in x direction
//				const auto dy = imgY.get(x1, y1);	// gradient's magnitude in y direction

//				// calculate magnitude and direction of the gradient
//				HOGGradient grad;
//				grad.magnitude = std::sqrt( (dx*dx) + (dy*dy) );		// gradient's overall magnitude
//				grad.direction = atan360(dy, dx);						// the gradient's direction

//				gradients.push_back(grad);

//			}

//			return gradients;

//		}



		/** get all individual gradients at the given location */
		Vector getHistogram(const K::ImageChannel& imgX, const K::ImageChannel& imgY, const int x, const int y, const std::vector<CellPoint>& region) const {

			// output histogram
			Vector res;
			res.resize(bins);

			// process each pixel
			for (size_t i = 0; i < region.size(); ++i) {

				const CellPoint p = region[i];

				// point within the image
				const int x1 = x+p.x;
				const int y1 = y+p.y;

				// clamp
				if (x1 < 0 || x1 >= imgX.getWidth())	{continue;}
				if (y1 < 0 || y1 >= imgX.getHeight())	{continue;}

				// calculate the centered derivatives
				const auto dx = imgX.get(x1, y1);	// gradient's magnitude in x direction
				const auto dy = imgY.get(x1, y1);	// gradient's magnitude in y direction

				// calculate magnitude and direction of the gradient
				const float mag = std::sqrt( (dx*dx) + (dy*dy) );		// gradient's overall magnitude
				const float dir = atan360(dy, dx);						// the gradient's direction in radians
				const float deg = dir * 180.0f / (float)M_PI;			// in degree

				// calculate bin-contribution [max 2 bins]
				// hereby add the impact factor based on the blur-window
				const Contributions c = getContribution(deg, mag * p.impact);

				if (1 == 1) {
					res[c.c1.bin] += c.c1.weight;	// split contribution
					res[c.c2.bin] += c.c2.weight;
				} else {
					res[c.c1.bin] += c.c1.weight;	// both to the same bin
					res[c.c1.bin] += c.c2.weight;	// both to the same bin
				}

			}

			// done
			return res;

		}


	public:

		/** a list of all pixels within a cell. (0,0) = cell-center */
		std::vector<CellPoint> getCellPoints(const Pattern p) const {

			std::vector<CellPoint> region;

			CellPoint dst(0,0,0);
			const ImagePoint center(0,0);

			if (p == CIRCULAR && cellSize.w != cellSize.h) {
				throw Exception("CIRCULAR pattern requires cellSize.w == cellSize.h");
			}

			const int sw2 = half(cellSize.w);
			const int sh2 = half(cellSize.w);

			// if the cell-size is odd, the end is included -> +1
			const int ew2 = sw2 + ( (cellSize.w % 2 == 1) ? 1 : 0);
			const int eh2 = sh2 + ( (cellSize.h % 2 == 1) ? 1 : 0);


			// process a square region...
			for (dst.y = -sh2; dst.y < +eh2; ++dst.y) {
				for (dst.x = -sw2; dst.x < +ew2; ++dst.x) {


					// impact factor based on sigma and distance from center
					// ensure the impact pattern is symmetric, also for even block sizes [no real center]
					const float dx = (float)dst.x + ( (cellSize.w % 2 == 0) ? 0.5f : 0.0f );
					const float dy = (float)dst.y + ( (cellSize.h % 2 == 0) ? 0.5f : 0.0f );
					dst.impact = std::exp( - ((dx*dx) + (dy*dy)) / (2.0f*sigma*sigma) );


					// pattern?
					if (p == RECTANGULAR) {
						region.push_back(dst);
					} else if (p == CIRCULAR) {
						// ...but use only points within a radius around the center
						const float d = center.distance(dst);
						if (d <= cellSize.w) {region.push_back(dst);}
					}

					std::cout << dst.x << "," << dst.y << ":" << dst.impact << "\t";

				}
				std::cout << std::endl;

			}

			return region;

		}

	};

}

#endif // HOG2_H
