# Aukafo
Aukafo står for automatisk katte fodrer. Dette projekt er softwarelageret til eksamensprojektet i Informatik B.

Man kan se en video om produktet på YouTube (https://youtu.be/m1rreF02XZE). Hjemmesiden, der bruges til at interagere med det fysiske produkt, findes [her](https://jehaj.github.io/automatisk-katte-fodrer/website/).

![Billede af Aukafo](https://github.com/jehaj/automatisk-katte-fodrer/blob/8c5f30031cff13d0d9858d51c921911a726a3ff3/Billede%20af%20Aukafo.jpg)

## Design valg
Produktet er færdigt. Jeg valgte at bruge en ESP8266 (mikrocontroller) i stedet for en Raspberry Pi. Det er både billigere og resulterer i en mindre formfaktor. Derudover betyder det også, at produktet er nemmere at sætte op - som vil sænke prisen yderligere, hvis det blev masseproduceret. 

## Fremtidige ændringer
Den elektroniske del af produktet virker, men der er problemer med at få fodret fra kassen ned til sneglen, der skubber fodret ned i skålen. Så det virker et par gange, men så ryger der ikke længere mad ned til sneglen, fordi det hober sig op i kassens munding. Det kunne måske løses ved at ændre designet af kassen ved f.eks. at gøre hullet større eller ændre opbevaringskassens design - designet er i øjeblikket (1). 
![Designs til foder opbevaringskassen](https://i.imgur.com/jBxNWDN.png)

Eftersom at serveren (APIen) kører på Heroku, sættes den til at sove, når den ikke bruges i længere tid. Det er et problem på grund af, at indstillingerne (tidspunkterne og mængden katten skal fodres) er kun "gemt" i en variabel og derfor bliver nulstillet når serveren vækkes. Målene fra vægten bliver gemt i en PostgreSQL database, så det er ikke et problem der. Løsningen kunne være at også gemme indstillingerne i en database.

## ToDo-list
- [x] Begynd på projekt
- [x] Server API (Node.js)
  - [x] Modtag data fra Raspberry Pi (post request)
  - [x] Gem data i DB (sqlite / mongodb)
  - [x] Være i stand  til at sende data til hjemmeside (json)
  - [x] Opdater indstillinger
    - [ ] ~~websocket opdaterer indstillinger til Raspberry Pi~~
    - [x] lav en get request fra mikrocontrolleren med intervaller for at se om indstillingerne har ændret sig.
- [ ] ~~Raspberry Pi (Python)~~
  - [ ] ~~Drej servomotor~~
  - [ ] ~~Få data fra vægt (maks 15 min efter foder er givet venter den)~~
  - [ ] ~~Send data til server (post request)~~
- [x] Hjemmeside (html/css/js css:bulma)
  - [x] Lav hjemmeside
    - [x] Indstillinger (tidspunkt på dagen og hvor meget foder skal af gives)
    - [x] Sektion til data
  - [x] Modtag data fra server API
  - [x] Vis graf på hjemmeside
- [x] Mikrocontroller (C++/Arduino) - I stedet for Raspberry Pi
  - [x] Drej servomotor
  - [x] Få data fra vægt
  - [x] Send data til server
