# automatisk-katte-fodrer
Softwarelager til eksamensprojekt i Informatik B.

## ToDo-list :/
- [x] Begynd på projekt
- [x] Server API (Node.js)
  - [x] Modtag data fra Raspberry Pi (post request)
  - [x] Gem data i DB (sqlite / mongodb)
  - [x] Være i stand  til at sende data til hjemmeside (json)
  - [] websocket opdaterer indstillinger til Raspberry Pi
- [ ] Raspberry Pi (Python)
  - [ ] Drej servomotor
  - [ ] Få data fra vægt (maks 15 min efter foder er givet venter den)
  - [ ] Send data til server (post request)
- [ ] Hjemmeside (html/css/js css:bulma)
  - [x] Lav hjemmeside
    - [x] Indstillinger (tidspunkt på dagen og hvor meget foder skal af gives)
    - [x] Sektion til data
  - [x] Modtag data fra server API
  - [x] Vis graf på hjemmeside
