# LedCube z modułem Bluetooth

**Autor**: Justyna Puz

## Spis treści
1. [Opis projektu](#opis-projektu)
2. [Funkcjonalności](#funkcjonalności)
3. [Komponenty](#komponenty)
4. [Schemat](#schemat)
5. [Szczegółowy opis działania elementów systemu](#szczegółowy-opis-działania-elementów-systemu)
   - [Diody LED](#diody-led)
   - [Tryby świecenia](#tryby-świecenia)
   - [Moduł Bluetooth](#moduł-bluetooth)
   - [Aplikacja](#aplikacja)
6. [Zdjęcia projektu](#zdjęcia-projektu)
   - [Lutowanie kostki](#lutowanie-kostki)
   - [Piny PA2 i PA3](#piny-pa2-i-pa3)
   - [Moduł Bluetooth](#moduł-bluetooth-2)
   - [Obsługa Bluetooth w aplikacji](#obsługa-bluetooth-w-aplikacji)

## Opis projektu

LedCube to kostka 4x4x4 zbudowana z 64 niebieskich diod LED. Do każdej pionowej kolumny i do każdego poziomu przylutowane są przewody, które umożliwiają sterowanie każdą diodą z osobna. Do mikrokontrolera STM32F401RE podłączony jest również moduł Bluetooth, który odpowiada za komunikację z aplikacją. Dodatkowym elementem jest podłączona dioda LED, umieszczona na płytce stykowej, która pomagała w sprawdzaniu połączenia i poprawności działania Bluetooth.

## Funkcjonalności

- 10 trybów świecenia
- Komunikacja z zewnętrzną aplikacją przez moduł Bluetooth
- Możliwość sterowania każdą diodą osobno
- Możliwość sprawdzenia stanu połączenia przy pomocy diody LED
- Możliwość wysyłania poleceń z dedykowanych aplikacji terminalowych Bluetooth

## Komponenty

- STM32F401RE
- 65 niebieskich diod LED
- Przewody połączeniowe
- Moduł Bluetooth HC-05
- Rezystory
- Płytka uniwersalna
- Kabel do podłączenia STM32 do komputera
- Telefon z systemem Android

## Schemat

(Schemat podłączeń komponentów. Dodaj tutaj rysunki lub diagramy, jeśli są dostępne.)

## Szczegółowy opis działania elementów systemu

### Diody LED

Diody LED (Light Emitting Diode) są półprzewodnikowymi elementami elektronicznymi, które emitują światło widzialne, gdy przepływa przez nie prąd elektryczny. W projekcie LedCube wykorzystano 64 niebieskie diody LED, rozmieszczone w kostce o wymiarach 4x4x4. Każda dioda jest kontrolowana indywidualnie za pomocą mikrokontrolera STM32F401RE, co umożliwia tworzenie różnorodnych efektów świetlnych i animacji. Połączenia są wykonane do każdej pionowej kolumny i każdego z czterech poziomów, co umożliwia sterowanie każdą diodą przez odpowiednie podawanie napięcia.

### Tryby świecenia

Projekt LedCube oferuje 10 różnych trybów świecenia, które można kontrolować z poziomu aplikacji mobilnej lub przez dedykowane aplikacje terminalowe.

Tryby:
- Flicker on
- Layer up and down
- Columns sideways
- Stomp up and down
- Flicker off
- Around Edge
- Rectangle
- Propeller
- Spiral
- All leds

### Moduł Bluetooth

Moduł Bluetooth HC-05 umożliwia bezprzewodową komunikację między LedCube a urządzeniem mobilnym. HC-05 jest powszechnie używanym modułem Bluetooth, który obsługuje standardy Bluetooth 2.0. W projekcie moduł ten jest odpowiedzialny za odbieranie komend z aplikacji mobilnej i przekazywanie ich do mikrokontrolera STM32F401RE. Komunikacja odbywa się przez interfejs UART, co pozwala na szybkie i niezawodne przesyłanie danych.

### Aplikacja

Aplikacja mobilna jest kluczowym elementem systemu, umożliwiając użytkownikowi interakcję z LedCube. Pozwala połączyć się z modułem, a później za pomocą interfejsu sterować trybami świecenia lub osobną diodą LED. Jest napisana na system Android.

## Zdjęcia projektu

### Lutowanie kostki

Podczas pierwszego etapu pracy, czyli tworzenia kostki LED, wybrałam drut, który później okazał się bardzo trudny do lutowania. Na tym etapie miałam dostępny lepszy sprzęt, jednak później, podczas lutowania przewodów, moja lutownica okazała się za słaba i zawodna.

### Piny PA2 i PA3

Po podłączeniu wszystkich przewodów okazało się, że na piny PA2 i PA3 nie można podawać napięcia w taki sposób, żeby diody LED działały. Musiałam przepiąć przewody do innych wyjść.

### Moduł Bluetooth

Po podłączeniu modułu Bluetooth nie byłam w stanie poprawnie odbierać komend z aplikacji terminalowej. Problemem okazał się warunek if w obsłudze przerwania oraz ustawienie baud rate w USART.

### Obsługa Bluetooth w aplikacji

Bardzo dużo problemów pojawiło się przy połączeniu Bluetooth. Gdy udało się uzyskać połączenie, okazało się, że wysyłanie komend nie działa. Po długich poszukiwaniach i debugowaniu okazało się, że problemem był brak znaku `\r` na końcu wysyłanej komendy, przez co przerwanie nie kończyło się poprawnie.
