// Impr_: Contrast da s ne kontrolira potenciometrom nego iz arduina (low prio)
// Impr_: Napravi da je brzina i akceleracija postotak, a ne vrijednost (low prio)
// Impr_: Use Sleep Modes
// Impr_: Promjeni sve konstante u macro constexpr i maybe smanji globalne varijable(low prio)
// Impr_: Promjeni imena funkcija i varijabli...they are horrible (low prio)
// Impr_: Uljepsat Main menu (low prio)
// Impr_: Dodati odbrojavanje do kraja graviranja i okretanja. (mid prio)
// Impr_: Dodati scroll bar (low prio) - Jos treba razmisliti kako bi to izgledalo. Back to (low prio)
// Impr_x: Spojit rotary encoder na interrupt arduino pin (mid prio)
// Impr_: Promjenit nacin vracanja u main meni. S tipkom na rotary encoderu (mid prio)
// Impr__1: Kada se vraca u main menu iz continus/bypass modea pitati da li da obrise part ili da ga sacuva (is blocker for Impr_6)

// Updates:
// ******************************************************************************************************************
// 4. Statistics
//   4.1 Prikazati na ekranu vrijeme iznmedu dva graviranja
//   4.2 Prikazati na ekranu vrijeme zamjene i strelicu koja bi oznacavala jesi iznad ili ispod
//       prosjeka
//   4.3 Dodati na ekran broj izgraviranih komad i mogucnost da se upise rucno broj komada
//   4.4 Dodati tipku na ekranu STAT na koju kad bi pritisnuo, otvorio bi se meni sa svom statistikkom
//       npr. vrijeme graviranja = prosjecno vrijeme +- pogreska, najbrze graviranje, najsporije, broj komada
//   4.5 Dodati mogucnost set_time() unutar continius modea
// ******************************************************************************************************************
// Trenutno je cijeli GUI podrazumjeva da se koristi 20x4 display...Nisam siguran kako bi se ponasao da stavimo manje/veci (nije update vise exploratory)

// #include "config.h" // Maybe not needed...
#include "display.h"
#include "screen.h"
#include "stepper.h"
#include "rotaryEncoder.h"
#include "mode.h"

void setup()
{

  initDisplay();
  welcomeScreen();
  mainMenuScreen(0);

  initRotaryEncoder();
  initSwitch();
}

void loop()
{
  unsigned short int position = selectLoop();
  selectMode(position);
}
