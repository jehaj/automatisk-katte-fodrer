# automatisk-katte-fodrer
Softwarelager til eksamensprojekt i Informatik B.

## ToDo-list :/
- [x] Begynd på projekt
- [ ] Server API (Node.js)
  - [ ] Modtag data fra Raspberry Pi (post request)
  - [ ] Gem data i DB (sqlite / mongodb)
  - [ ] Være i stand  til at sende data til hjemmeside (json)
  - [ ] websocket opdaterer indstillinger til Raspberry Pi
- [ ] Raspberry Pi (Python)
  - [ ] Drej servomotor
  - [ ] Få data fra vægt (maks 15 min efter foder er givet venter den)
  - [ ] Send data til server (post request)
- [ ] Hjemmeside (html/css/js css:bulma)
  - [ ] Lav hjemmeside
    - [ ] Indstillinger (tidspunkt på dagen og hvor meget foder skal af gives)
    - [ ] Sektion til data
  - [ ] Modtag data fra server API
  - [ ] Vis graf på hjemmeside
