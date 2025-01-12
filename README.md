# DumbHack :: Survival
#### DumbHack :: Survival este un joc de supraviețuire captivant în care personajul principal, un student ambițios, își propune să își demonstreze abilitățile la un maraton de programare. Totuși, ca o ironie a sorții, acesta întârzie la competiție. Între timp, situația se schimbă dramatic: un virus cibernetic scapă de sub control și transformă toți ceilalți participanți într-o armată de zombi, determinați să oprească pe oricine le stă în cale. Eroul nostru trebuie acum să lupte împotriva acestor zombi și, în același timp, să găsească o cale de a neutraliza virusul, restabilind ordinea în competiție. Va reuși el să supraviețuiască și să readucă lucrurile la normal?

Pentru a vizualiza un demo al jocului puteti apăsa pe următoarea imagine.
[![DumbHack Survival](https://img.youtube.com/vi/rFHtNtfOw5g/maxresdefault.jpg)](https://www.youtube.com/watch?v=rFHtNtfOw5g&ab_channel=UrsuAlexandruPetrut)


## Assets
#### <b>Aproape</b> toate assets-urile <b>vizuale</b> din acest proiect sunt create de mine, folosind [acest tool](https://www.pixilart.com/), mai puțin : [acesta](assets/Treasure.png) (Treasure.png) care a fost luat de [aici](https://skalding.itch.io/chest-16x16-open-and-closed).

#### Efectele audio din joc au fost luate de aici: 
  -> Sound Effect by <a href="https://pixabay.com/users/freesound_community-46691455/?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=31697">freesound_community</a> from <a href="https://pixabay.com/sound-effects//?utm_source=link-attribution&utm_medium=referral&utm_campaign=music&utm_content=31697">Pixabay</a> (main music)  
  -> [swingSound](https://mixkit.co/free-sound-effects/hit/) (Impact of a strong punch)  
  -> [zombiePunch](https://mixkit.co/free-sound-effects/blow/) (Impact of a blow)  
  -> [TreasureUnlock](https://mixkit.co/free-sound-effects/arcade/) (Retro arcade casino notification)  
  -> [DrinkSoda](https://mixkit.co/free-sound-effects/drink/) (Sip of water)  
  -> [Kiss](https://mixkit.co/free-sound-effects/kiss/) (Cartoon friendly kiss)
  -> [SpecialTrapSound](https://mixkit.co/free-sound-effects/hurt/) (Ow exclamation of pain)

## Fonts
Font-ul textului din proiect a fost downloadat de [aici](https://font.download/font/arial).

## Surse cod extern

În acest proiect, am folosit algoritmul [AStar](ext/AStar) din surse externe:
  1. **[a-star](https://github.com/daancode/a-star)** - [Licența MIT](https://github.com/daancode/a-star?tab=MIT-1-ov-file)
    
  > De menționat faptul că am adus modificări proprii asupra sursei externe, pentru a putea fi implementată în cadrul acestui proiect.

## Instrucțiuni de compilare

Proiectul este configurat cu CMake.

Instrucțiuni pentru terminal:

0. Biblioteci necesare pe Linux (presupunem sistem de operare bazat pe Debian)
```sh
sudo apt-get update && \
  sudo apt-get install libxrandr-dev \
    libxcursor-dev \
    libudev-dev \
    libopenal-dev \
    libflac-dev \
    libvorbis-dev \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libdrm-dev \
    libgbm-dev \
    libfreetype6-dev
```

Dacă lipsesc și alte biblioteci, ștergeți folder-ul de build de la pasul 1 și reconfigurați proiectul după ce ați instalat ce lipsea.

1. Pasul de configurare
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

Sau pe Windows cu GCC:
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
```

La acest pas putem cere să generăm fișiere de proiect pentru diverse medii de lucru.


2. Pasul de compilare
```sh
cmake --build build --config Debug --parallel 6
```

Cu opțiunea `parallel` specificăm numărul de fișiere compilate în paralel.

3. Pasul de instalare (opțional)
```sh
cmake --install build --config Debug --prefix install_dir
```

Vezi și [`scripts/cmake.sh`](scripts/cmake.sh).

## Resurse

- [SFML](https://github.com/SFML/SFML/tree/2.6.1) (Zlib)
  - [OpenAL](https://openal-soft.org/) (LGPL): din cauza licenței, trebuie distribuită ca shared library
- adăugați trimiteri către resursele externe care v-au ajutat sau pe care le-ați folosit
