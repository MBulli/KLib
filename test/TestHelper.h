/*
 * TestHelper.h
 *
 *  Created on: Dec 18, 2013
 *      Author: kazu
 */

#ifndef TESTHELPER_H_
#define TESTHELPER_H_

#include <cmath>
#include <cstdint>

class TestHelper {

public:

	/** get some random data */
	static uint8_t* getRandom(unsigned int size) {
		uint8_t* rand = (uint8_t*) malloc(size);
		for (unsigned int i = 0; i < size; ++i) {
			rand[i] = (uint8_t) ::rand();
		}
		return rand;
	}

	static std::string getLoremIpsum() {
		return
				"Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
				"Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat."
				"Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi."
				"Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat."
				"Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis."
				"At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, At accusam aliquyam diam diam dolore dolores duo eirmod eos erat, et nonumy sed tempor et et invidunt justo labore Stet clita ea et gubergren, kasd magna no rebum. sanctus sea sed takimata ut vero voluptua. est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat."
				"Consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus."
				"Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet. Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore et dolore magna aliquyam erat, sed diam voluptua. At vero eos et accusam et justo duo dolores et ea rebum. Stet clita kasd gubergren, no sea takimata sanctus est Lorem ipsum dolor sit amet."
				"Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat."
				"Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat. Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi."
				"Nam liber tempor cum soluta nobis eleifend option congue nihil imperdiet doming id quod mazim placerat facer possim assum. Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo";
	}

	static std::string getBlindText1() {
		return
				"Seit zwei Jahren ist meine Arbeit in Düsseldorf. Meine Familie lebt dagegen in Hamburg. Und dazwischen ich, aber ganz cool. Vollbremskombination aus Ampel oder Einfädeln oder beides auf einmal. Geht nur mit Tricks. Eben noch kurz auf die A 52. Schon vielversprechend lebhaft. Hinter dem Breitscheider Kreuz geht es richtig los. Stau auf der A 3 bis Oberhausen. Danach entspannt es sich auch nur deshalb, weil enge Baustellen mit rüden Geschwindigkeitsbegrenzungen zum gleichmässigen Rollen zwingen. Es wird links überholt, es wird rechts überholt. Es wird gar nichts mehr, alles steht und macht lange Gesichter. Ich dagegen wechsle die Cassette. Es geht weiter. Vor und hinter mir hektische Spurenwechsel. So zieht sich das Stück A 2 bis zum Recklinghauser Kreuz. Der erhofften Entspannung folgt zuverlässig der Vollfrust. Die A 43 bis Münster ist genauso voll wie das Kamener Kreuz zur Rush-hour. Auf der A 1 ist dann endgültig Schluss mit lustig. Alles dümpelt auf der Überholspur. Natürlich mit 90. Rechts geht es schneller, irrerweise wegen der Lkws. Die wollen nämlich alle noch vor zehn zu Hause sein. Osnabrück. Dammer Berge. Tanken, weil kleiner Tank. Nach Wildeshausen wird die Autobahn dreispurig. Klasse! Alles stürmt nach links, auch ein Kadett City mit Bochumer Kennzeichen. Bleibt hartnäckig. Blinker bringt auch nichts. Lichthupe ebenfalls zwecklos. Muss rechts vorbei. Ein Mittelscheitel macht den Breiten. Der Verkehr verzieht sich. Nach Stuckenborstel gehe ich vom Gas nicht mehr runter. Den Abzweig zum Elbtunnel mal wieder viel zu schnell genommen. Der Rest geht schnell. Entscheide mich natürlich wie immer für die linke Röhre, um dann nach Tunnelende dramatisch blitzartig vier Spuren nach rechts in die Ausfahrt hineinzubremsen. Das einzige, was auf der Stresemann wieder aufhält, ist eine kuriose Ampelschaltung. Am Phantom der Oper links, auf dem Ring einmal rundrum bis zum Winterhuder Marktplatz, dahinter noch mal links, zum Stadtpark hinunter. Ich bin da. Wieder zu spät. Alles schläft schon. Samstag. Sonntag. Deutschland guckt Tagesschau. Ich gucke in den linken Aussenspiegel. Dann drei Spuren rüber wieder in die linke Röhre. Diesmal doppelt so schnell durch den Tunnel wie auf dem Hinweg. Bleibe auf der linken Spur bis zum Abzweig Richtung Bremen. Der ist zweispurig, deshalb gibt es das beliebte Abbiegen-im-letzten-Moment-Spiel. Weil offensichtlich die Geschwindigkeitsbegrenzung vergessen wurde, bin ich drei Minuten später schon auf der Bremer Autobahn. Die Überholspur ist frei. Ein Fünfer will es wissen. Muss ein i sein, er lässt sich nicht abschütteln. Wie immer auf dem Rückweg säuft der Wagen wie ein Loch. An der Raststätte Wildeshausen bin ich fällig. Brauche auch noch was Süsses. Dann leiste ich mir mal wieder den höllisch teuren Trinkjoghurt in der ekligen Plastikflasche. Pinkeln kann entfallen. Superkurzer Tankstopp. Der Verkehr nimmt zu, die Tempo-100-Schilder nehmen auch zu. Der Liter von dem süssen Zeug ist weg, bevor ich in Osnabrück bin. Vor dem Beifahrersitz sammelt sich der Müll. Endlich sind die Laster da. Dann regnet es auch noch. Wie immer warte ich auf das kurze dreispurige Steigungsstück im Tecklenburger Wald, um mich an die Spitze der Schlange zu setzen. Die dritte Spur kommt, und mein Plan wird von einem japanischen, wild getunten Insekt mit Essener Kennzeichen vereitelt. Nunmehr prasselnder Regen tut sein übriges. Noch vor Münster verschwindet er so schnell, wie er gekommen ist. Die Strasse ist trocken. Grossartig! Jetzt geht es nämlich auf die 43 Richtung Recklinghausen, meine private Rennstrecke. 60 Kilometer, die ich schon in knapp 20 Minuten geschafft habe. Ich biege auf die besagte Autobahn, natürlich sofort nach links auf die Überholspur. Muss mich jetzt leider unbeliebt machen. Einer zeigt mir den Stinkefinger. Ich werfe Kusshändchen, das macht sie besonders fertig. Und ich gebe Gas, gerne auch mit Zurückschalten. Manche Lkw-Fahrer, an denen ich vorbeizische, grüssen freundlich mit Lichthupe. Ich kann leider nicht zurückgrüssen, habe keine Zeit dafür. Das Recklinghauser Kreuz ist da und ab auf die A 2 Richtung Oberhausen. Die nächste Baustelle hat es in sich. Da sind die Spuren so eng, dass man sich bei überhöhter Geschwindigkeit nicht mal eine Kippe anzünden kann, ohne über diese gelben Knopfmarkierungen zu fahren. Ich spüre diese Drecksdinger einzeln, so hart ist mein Wagen gefedert. Zwischendurch Zwischenspurts. Mal wieder mehr Radarfallenschilder als Radarfallen. Oberhausen kommt und geht. Das Breitscheider Kreuz auch. Ich biege auf die A 52 und bleibe dabei, bis ich mal wieder viel zu schnell in die Stadt einrolle. Kurz vor dem DEG-Stadion hole ich mir noch ein paar Alt an der Tanke. Die Lindemann nach Süden, links auf die Grafenberger und dann gleich wieder rechts. Ich bin da. Blick zur Uhr, Zeit nehmen. Jetzt schnell den ganzen Krempel rauf in die Wohnung. Glotze an, Spätnachrichten. Einschlafen. Montag. Dienstag. Mittwoch. Donnerstag. Freitag. Am Nachmittag ist es am schlimmsten. Stadtauswärts Richtung Flughafen. Der letzte Abzweig ist besonders schlau.";
	}

	static std::string getLoremIpsum(unsigned int cnt) {
		std::string ret = "";
		for (unsigned int i = 0; i < cnt; ++i) {
			ret += getLoremIpsum();
		}
		return ret;
	}

};


#endif /* TESTHELPER_H_ */
