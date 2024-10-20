# BankSimul backend

## Ympäristömuuttujat

BankSimul backend odottaa seuraavien ympäristömuuttujien olevan saatavilla:

- `DATABASE` Tietokannan nimi.
- `DATABASE_HOST` Tietokantapalvelimen osoite.
- `DATABASE_PORT` Tietokantapalvelimen portti.
- `DATABASE_USERNAME` MySQL-käyttäjänimi, jolla on oikeudet tietokantaan.
- `DATABASE_PASSWORD` Yllä olevan käyttäjän salasana.
- `JWT_SECRET_KEY` JWT:t allekirjoitetaan tällä avaimella.

Nämä voi asettaa esimerkiksi seuraavasti. Kopioi repositoryn juuressa tiedosto
`compose-dev.yml` tiedostoon `compose.yml`. Lue tiedosto läpi, ja tee haluamasi
muutokset. Tiedostosta näkee mitä ympäristömuuttujia backend-palvelu asettaa. Aseta
nämä muuttujat tiedostossa `.env`. Docker Compose lukee tiedoston käynnistyksessä,
ja ympäristömuuttujat asetetaan. Että ympäristömuuttujat siirtyisivät Docker Composelta
backendille, pitää ne erikseen asettaa `compose.yml` tiedostossa.

Tiedosto `compose.yml` on toistaiseksi listattuna `.gitignore`ssa,
