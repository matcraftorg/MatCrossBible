/***************************************************************************
 *   MatCrossBible  (old name: CrossBgBible)                               *
 *   Copyright (C) 2007-2020 by MatCraft, Bulgaria                         *
 *   matcraft.org@gmail.com                                                *
 *   http://www.matcraft.org/  (old site: http://www.crossbgbible.com/)    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "trstrings.h"

// http://www.bibleserver.com/ -- Имената на книгите на различни езици.

//
void TrStrings::initBooksBulgarian()
{
  bookNameArr[0]  = QString("Битие");                                   bookShortNameArr[0]  = QString("Битие");                           bookMinNameArr[0]  = QString("Битие");//Бит.
  bookNameArr[1]  = QString("Изход");                                   bookShortNameArr[1]  = QString("Изход");                           bookMinNameArr[1]  = QString("Изход");//Изх.
  bookNameArr[2]  = QString("Левит");                                   bookShortNameArr[2]  = QString("Левит");                           bookMinNameArr[2]  = QString("Левит");//Лев.
  bookNameArr[3]  = QString("Числа");                                   bookShortNameArr[3]  = QString("Числа");                           bookMinNameArr[3]  = QString("Числа");//Чис.
  bookNameArr[4]  = QString("Второзаконие");                            bookShortNameArr[4]  = QString("Второзаконие");                    bookMinNameArr[4]  = QString("Втор.");//Вт.
  bookNameArr[5]  = QString("Исус Навин");                              bookShortNameArr[5]  = QString("Исус Навин");                      bookMinNameArr[5]  = QString("И.Н.");//И.Н.
  bookNameArr[6]  = QString("Съдии");                                   bookShortNameArr[6]  = QString("Съдии");                           bookMinNameArr[6]  = QString("Съдии");//Съд.
  bookNameArr[7]  = QString("Рут");                                     bookShortNameArr[7]  = QString("Рут");                             bookMinNameArr[7]  = QString("Рут");//Рут
  bookNameArr[8]  = QString("1 Книга на Царете");                       bookShortNameArr[8]  = QString("1 Царе");                          bookMinNameArr[8]  = QString("1Царе");//1Цар.
  bookNameArr[9]  = QString("2 Книга на Царете");                       bookShortNameArr[9]  = QString("2 Царе");                          bookMinNameArr[9]  = QString("2Царе");//2Цар.
  bookNameArr[10] = QString("3 Книга на Царете");                       bookShortNameArr[10] = QString("3 Царе");                          bookMinNameArr[10] = QString("3Царе");//3Цар.
  bookNameArr[11] = QString("4 Книга на Царете");                       bookShortNameArr[11] = QString("4 Царе");                          bookMinNameArr[11] = QString("4Царе");//4Цар.
  bookNameArr[12] = QString("1 Книга на Летописите");                   bookShortNameArr[12] = QString("1 Летописи");                      bookMinNameArr[12] = QString("1Лет.");//1Лет.
  bookNameArr[13] = QString("2 Книга на Летописите");                   bookShortNameArr[13] = QString("2 Летописи");                      bookMinNameArr[13] = QString("2Лет.");//2Лет.
  bookNameArr[14] = QString("Ездра");                                   bookShortNameArr[14] = QString("Ездра");                           bookMinNameArr[14] = QString("Ездра");//Езд.
  bookNameArr[15] = QString("Неемия");                                  bookShortNameArr[15] = QString("Неемия");                          bookMinNameArr[15] = QString("Неемия");//Неем.
  bookNameArr[16] = QString("Естир");                                   bookShortNameArr[16] = QString("Естир");                           bookMinNameArr[16] = QString("Естир");//Ест.
  bookNameArr[17] = QString("Йов");                                     bookShortNameArr[17] = QString("Йов");                             bookMinNameArr[17] = QString("Йов");//Йов
  bookNameArr[18] = QString("Псалми");                                  bookShortNameArr[18] = QString("Псалми");                          bookMinNameArr[18] = QString("Пс.");//Пс.
  bookNameArr[19] = QString("Притчи");                                  bookShortNameArr[19] = QString("Притчи");                          bookMinNameArr[19] = QString("Пр.");//Пр.
  bookNameArr[20] = QString("Еклисиаст");                               bookShortNameArr[20] = QString("Еклисиаст");                       bookMinNameArr[20] = QString("Екл.");//Екл.
  bookNameArr[21] = QString("Песен на песните");                        bookShortNameArr[21] = QString("Песен на песните");                bookMinNameArr[21] = QString("П.П.");//П.П.
  bookNameArr[22] = QString("Исая");                                    bookShortNameArr[22] = QString("Исая");                            bookMinNameArr[22] = QString("Исая");//Ис.
  bookNameArr[23] = QString("Еремия");                                  bookShortNameArr[23] = QString("Еремия");                          bookMinNameArr[23] = QString("Еремия");//Ер.
  bookNameArr[24] = QString("Плачът на Еремия");                        bookShortNameArr[24] = QString("Плачът на Еремия");                bookMinNameArr[24] = QString("Пл.Ер.");//Пл.Ер.
  bookNameArr[25] = QString("Езекиил");                                 bookShortNameArr[25] = QString("Езекиил");                         bookMinNameArr[25] = QString("Езек.");//Езек.
  bookNameArr[26] = QString("Даниил");                                  bookShortNameArr[26] = QString("Даниил");                          bookMinNameArr[26] = QString("Дан.");//Дан.
  bookNameArr[27] = QString("Осия");                                    bookShortNameArr[27] = QString("Осия");                            bookMinNameArr[27] = QString("Осия");//Ос.
  bookNameArr[28] = QString("Йоил");                                    bookShortNameArr[28] = QString("Йоил");                            bookMinNameArr[28] = QString("Йоил");//Йоил
  bookNameArr[29] = QString("Амос");                                    bookShortNameArr[29] = QString("Амос");                            bookMinNameArr[29] = QString("Амос");//Ам.
  bookNameArr[30] = QString("Авдий");                                   bookShortNameArr[30] = QString("Авдий");                           bookMinNameArr[30] = QString("Авдий");//Авд.
  bookNameArr[31] = QString("Йона");                                    bookShortNameArr[31] = QString("Йона");                            bookMinNameArr[31] = QString("Йона");//Йона
  bookNameArr[32] = QString("Михей");                                   bookShortNameArr[32] = QString("Михей");                           bookMinNameArr[32] = QString("Михей");//Мих.
  bookNameArr[33] = QString("Наум");                                    bookShortNameArr[33] = QString("Наум");                            bookMinNameArr[33] = QString("Наум");//Наум
  bookNameArr[34] = QString("Авакум");                                  bookShortNameArr[34] = QString("Авакум");                          bookMinNameArr[34] = QString("Авак.");//Авак.
  bookNameArr[35] = QString("Софония");                                 bookShortNameArr[35] = QString("Софония");                         bookMinNameArr[35] = QString("Соф.");//Соф.
  bookNameArr[36] = QString("Агей");                                    bookShortNameArr[36] = QString("Агей");                            bookMinNameArr[36] = QString("Агей");//Аг.
  bookNameArr[37] = QString("Захария");                                 bookShortNameArr[37] = QString("Захария");                         bookMinNameArr[37] = QString("Зах.");//Зах.
  bookNameArr[38] = QString("Малахия");                                 bookShortNameArr[38] = QString("Малахия");                         bookMinNameArr[38] = QString("Мал.");//Мал.

  bookNameArr[39] = QString("2 Ездра");                                 bookShortNameArr[39] = QString("2 Ездра");                         bookMinNameArr[39] = QString("2Ездра");//2Езд.
  bookNameArr[40] = QString("Товита");                                  bookShortNameArr[40] = QString("Товита");                          bookMinNameArr[40] = QString("Товита");//Тов.
  bookNameArr[41] = QString("Иудит");                                   bookShortNameArr[41] = QString("Иудит");                           bookMinNameArr[41] = QString("Иудит");//Иуд.
  bookNameArr[42] = QString("Премъдрост Соломонова");                   bookShortNameArr[42] = QString("Премъдрост Соломонова");           bookMinNameArr[42] = QString("Пр.Сол.");//Пр.Сол.
  bookNameArr[43] = QString("Премъдрост на Исус, син Сирахов");         bookShortNameArr[43] = QString("Исус Сирахов");                    bookMinNameArr[43] = QString("Сирах");//Ис.Сир.
  bookNameArr[44] = QString("Послание на Еремия");                      bookShortNameArr[44] = QString("Послание на Еремия");              bookMinNameArr[44] = QString("Пос.Ер.");//Пос.Ер.
  bookNameArr[45] = QString("Варуха");                                  bookShortNameArr[45] = QString("Варуха");                          bookMinNameArr[45] = QString("Варуха");//Вар.
  bookNameArr[46] = QString("1 Макавей");                               bookShortNameArr[46] = QString("1 Макавей");                       bookMinNameArr[46] = QString("1Мак.");//1Мак.
  bookNameArr[47] = QString("2 Макавей");                               bookShortNameArr[47] = QString("2 Макавей");                       bookMinNameArr[47] = QString("2Мак.");//2Мак.
  bookNameArr[48] = QString("3,4 Макавей");                             bookShortNameArr[48] = QString("3,4 Макавей");                     bookMinNameArr[48] = QString("3,4Мак.");//3,4Мак.
  bookNameArr[49] = QString("3 Ездра");                                 bookShortNameArr[49] = QString("3 Ездра");                         bookMinNameArr[49] = QString("3Ездра");//3Езд.

  bookNameArr[50] = QString("Евангелие според Матей");                  bookShortNameArr[50] = QString("Матей");                           bookMinNameArr[50] = QString("Матей");//Матей
  bookNameArr[51] = QString("Евангелие според Марк");                   bookShortNameArr[51] = QString("Марк");                            bookMinNameArr[51] = QString("Марк");//Марк
  bookNameArr[52] = QString("Евангелие според Лука");                   bookShortNameArr[52] = QString("Лука");                            bookMinNameArr[52] = QString("Лука");//Лука
  bookNameArr[53] = QString("Евангелие според Йоан");                   bookShortNameArr[53] = QString("Йоан");                            bookMinNameArr[53] = QString("Йоан");//Йоан
  bookNameArr[54] = QString("Деяния на Апостолите");                    bookShortNameArr[54] = QString("Деяния");                          bookMinNameArr[54] = QString("Д.А.");//Д.А.

  bookNameArr[55] = QString("Римляни");                                 bookShortNameArr[55] = QString("Римляни");                         bookMinNameArr[55] = QString("Рим.");//Рим.
  bookNameArr[56] = QString("1 Коринтяни");                             bookShortNameArr[56] = QString("1 Коринтяни");                     bookMinNameArr[56] = QString("1Кор.");//1Кор.
  bookNameArr[57] = QString("2 Коринтяни");                             bookShortNameArr[57] = QString("2 Коринтяни");                     bookMinNameArr[57] = QString("2Кор.");//2Кор.
  bookNameArr[58] = QString("Галатяни");                                bookShortNameArr[58] = QString("Галатяни");                        bookMinNameArr[58] = QString("Гал.");//Гал.
  bookNameArr[59] = QString("Ефесяни");                                 bookShortNameArr[59] = QString("Ефесяни");                         bookMinNameArr[59] = QString("Ефес.");//Еф.
  bookNameArr[60] = QString("Филипяни");                                bookShortNameArr[60] = QString("Филипяни");                        bookMinNameArr[60] = QString("Филип.");//Фил.
  bookNameArr[61] = QString("Колосяни");                                bookShortNameArr[61] = QString("Колосяни");                        bookMinNameArr[61] = QString("Колос.");//Кол.
  bookNameArr[62] = QString("1 Солунци");                               bookShortNameArr[62] = QString("1 Солунци");                       bookMinNameArr[62] = QString("1Сол.");//1Сол.
  bookNameArr[63] = QString("2 Солунци");                               bookShortNameArr[63] = QString("2 Солунци");                       bookMinNameArr[63] = QString("2Сол.");//2Сол.
  bookNameArr[64] = QString("1 Тимотей");                               bookShortNameArr[64] = QString("1 Тимотей");                       bookMinNameArr[64] = QString("1Тим.");//1Тим.
  bookNameArr[65] = QString("2 Тимотей");                               bookShortNameArr[65] = QString("2 Тимотей");                       bookMinNameArr[65] = QString("2Тим.");//2Тим.
  bookNameArr[66] = QString("Тит");                                     bookShortNameArr[66] = QString("Тит");                             bookMinNameArr[66] = QString("Тит");//Тит
  bookNameArr[67] = QString("Филимон");                                 bookShortNameArr[67] = QString("Филимон");                         bookMinNameArr[67] = QString("Филим.");//Филим.
  bookNameArr[68] = QString("Евреи");                                   bookShortNameArr[68] = QString("Евреи");                           bookMinNameArr[68] = QString("Евреи");//Евр.

  bookNameArr[69] = QString("Яков");                                    bookShortNameArr[69] = QString("Яков");                            bookMinNameArr[69] = QString("Яков");//Як.
  bookNameArr[70] = QString("1 Петър");                                 bookShortNameArr[70] = QString("1 Петър");                         bookMinNameArr[70] = QString("1Пет.");//1Пет.
  bookNameArr[71] = QString("2 Петър");                                 bookShortNameArr[71] = QString("2 Петър");                         bookMinNameArr[71] = QString("2Пет.");//2Пет.
  bookNameArr[72] = QString("1 Йоан");                                  bookShortNameArr[72] = QString("1 Йоан");                          bookMinNameArr[72] = QString("1Йоан");//1Йн.
  bookNameArr[73] = QString("2 Йоан");                                  bookShortNameArr[73] = QString("2 Йоан");                          bookMinNameArr[73] = QString("2Йоан");//2Йн.
  bookNameArr[74] = QString("3 Йоан");                                  bookShortNameArr[74] = QString("3 Йоан");                          bookMinNameArr[74] = QString("3Йоан");//3Йн.
  bookNameArr[75] = QString("Юда");                                     bookShortNameArr[75] = QString("Юда");                             bookMinNameArr[75] = QString("Юда");//Юда

  bookNameArr[76] = QString("Откровение на Йоан");                      bookShortNameArr[76] = QString("Откровение");                      bookMinNameArr[76] = QString("Откр.");//Откр.
}

// https://cs.wikipedia.org/wiki/Bible
// https://cs.wikipedia.org/wiki/Starý_zákon
// https://cs.wikipedia.org/wiki/Nový_zákon
// https://cs.wikipedia.org/wiki/Biblická_kniha
// https://cs.wikipedia.org/wiki/Apokryf
// http://www.kubak.cz/bible/seznam.htm
// http://www.vira.cz/otazky/Zkratky-knih-v-Bibli-biblicke-citace.html
// http://www.abcviry.cz/index.php/vse-o-nabozenstvi/o-bibli/104-razeni-knih-bible
void TrStrings::initBooksCzech()
{
  bookNameArr[0]  = QString("Genesis"); /*1 Mojžíšova*/                 bookShortNameArr[0]  = QString("Genesis");                         bookMinNameArr[0]  = QString("Gen");//Gn /*1M,1Mojž*/
  bookNameArr[1]  = QString("Exodus"); /*2 Mojžíšova*/                  bookShortNameArr[1]  = QString("Exodus");                          bookMinNameArr[1]  = QString("Exod");//Ex /*2M,2Mojž*/
  bookNameArr[2]  = QString("Leviticus"); /*3 Mojžíšova*/               bookShortNameArr[2]  = QString("Leviticus");                       bookMinNameArr[2]  = QString("Levit");//Lv /*3M,3Mojž*/
  bookNameArr[3]  = QString("Numeri"); /*4 Mojžíšova*/                  bookShortNameArr[3]  = QString("Numeri");                          bookMinNameArr[3]  = QString("Numer");//Nu /*4M,4Mojž*/
  bookNameArr[4]  = QString("Deuteronomium"); /*5 Mojžíšova*/           bookShortNameArr[4]  = QString("Deuteronomium");                   bookMinNameArr[4]  = QString("Deut");//Dt /*5M,5Mojž*/
  bookNameArr[5]  = QString("Jozue");                                   bookShortNameArr[5]  = QString("Jozue");                           bookMinNameArr[5]  = QString("Jozue");//Joz
  bookNameArr[6]  = QString("Soudců");                                  bookShortNameArr[6]  = QString("Soudců");                          bookMinNameArr[6]  = QString("Soudců");//Soud
  bookNameArr[7]  = QString("Rút");                                     bookShortNameArr[7]  = QString("Rút");                             bookMinNameArr[7]  = QString("Rút");//Rút
  bookNameArr[8]  = QString("1 Samuelova");                             bookShortNameArr[8]  = QString("1 Samuelova");                     bookMinNameArr[8]  = QString("1Sam");//1Sam
  bookNameArr[9]  = QString("2 Samuelova");                             bookShortNameArr[9]  = QString("2 Samuelova");                     bookMinNameArr[9]  = QString("2Sam");//2Sam
  bookNameArr[10] = QString("1 Královská");                             bookShortNameArr[10] = QString("1 Královská");                     bookMinNameArr[10] = QString("1Král");//1Král
  bookNameArr[11] = QString("2 Královská");                             bookShortNameArr[11] = QString("2 Královská");                     bookMinNameArr[11] = QString("2Král");//2Král
  bookNameArr[12] = QString("1 Paralipomenon");                         bookShortNameArr[12] = QString("1 Paralipomenon");                 bookMinNameArr[12] = QString("1Par");//1Par
  bookNameArr[13] = QString("2 Paralipomenon");                         bookShortNameArr[13] = QString("2 Paralipomenon");                 bookMinNameArr[13] = QString("2Par");//2Par
  bookNameArr[14] = QString("Ezdráš");                                  bookShortNameArr[14] = QString("Ezdráš");                          bookMinNameArr[14] = QString("Ezdráš");//Ezd
  bookNameArr[15] = QString("Nehemiáš");                                bookShortNameArr[15] = QString("Nehemiáš");                        bookMinNameArr[15] = QString("Nehem");//Neh
  bookNameArr[16] = QString("Ester");                                   bookShortNameArr[16] = QString("Ester");                           bookMinNameArr[16] = QString("Ester");//Est
  bookNameArr[17] = QString("Jób");                                     bookShortNameArr[17] = QString("Jób");                             bookMinNameArr[17] = QString("Jób");//Jób
  bookNameArr[18] = QString("Žalmy");                                   bookShortNameArr[18] = QString("Žalmy");                           bookMinNameArr[18] = QString("Žalmy");//Z
  bookNameArr[19] = QString("Přísloví");                                bookShortNameArr[19] = QString("Přísloví");                        bookMinNameArr[19] = QString("Přísl");//Př,Přísl
  bookNameArr[20] = QString("Kazatel");                                 bookShortNameArr[20] = QString("Kazatel");                         bookMinNameArr[20] = QString("Kazat");//Kaz,Kazat
  bookNameArr[21] = QString("Píseň písní");                             bookShortNameArr[21] = QString("Píseň písní");                     bookMinNameArr[21] = QString("Píseň");//Pís
  bookNameArr[22] = QString("Izajáš");                                  bookShortNameArr[22] = QString("Izajáš");                          bookMinNameArr[22] = QString("Izaj");//Iz
  bookNameArr[23] = QString("Jeremjáš");                                bookShortNameArr[23] = QString("Jeremjáš");                        bookMinNameArr[23] = QString("Jerem");//Jer
  bookNameArr[24] = QString("Pláč Jeremjášův");                         bookShortNameArr[24] = QString("Pláč Jeremjášův");                 bookMinNameArr[24] = QString("Pláč");//Pláč
  bookNameArr[25] = QString("Ezechiel");                                bookShortNameArr[25] = QString("Ezechiel");                        bookMinNameArr[25] = QString("Ezech");//Ez,Ezech
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Daniel");//Dan
  bookNameArr[27] = QString("Ozeáš");                                   bookShortNameArr[27] = QString("Ozeáš");                           bookMinNameArr[27] = QString("Ozeáš");//Oz
  bookNameArr[28] = QString("Jóel");                                    bookShortNameArr[28] = QString("Jóel");                            bookMinNameArr[28] = QString("Jóel");//Jl,Jóel
  bookNameArr[29] = QString("Ámos");                                    bookShortNameArr[29] = QString("Ámos");                            bookMinNameArr[29] = QString("Ámos");//Ám
  bookNameArr[30] = QString("Abdijáš");                                 bookShortNameArr[30] = QString("Abdijáš");                         bookMinNameArr[30] = QString("Abd");//Abd
  bookNameArr[31] = QString("Jonáš");                                   bookShortNameArr[31] = QString("Jonáš");                           bookMinNameArr[31] = QString("Jonáš");//Jon
  bookNameArr[32] = QString("Micheáš");                                 bookShortNameArr[32] = QString("Micheáš");                         bookMinNameArr[32] = QString("Mich");//Mi,Mich
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nahum");//Na,Nah
  bookNameArr[34] = QString("Abakuk");                                  bookShortNameArr[34] = QString("Abakuk");                          bookMinNameArr[34] = QString("Abak");//Abk,Abak
  bookNameArr[35] = QString("Sofonjáš");                                bookShortNameArr[35] = QString("Sofonjáš");                        bookMinNameArr[35] = QString("Sofon");//Sf,Sofon
  bookNameArr[36] = QString("Ageus");                                   bookShortNameArr[36] = QString("Ageus");                           bookMinNameArr[36] = QString("Ageus");//Ag
  bookNameArr[37] = QString("Zacharjáš");                               bookShortNameArr[37] = QString("Zacharjáš");                       bookMinNameArr[37] = QString("Zachar");//Za,Zach
  bookNameArr[38] = QString("Malachiáš)");                              bookShortNameArr[38] = QString("Malachiáš)");                      bookMinNameArr[38] = QString("Malach");//Mal

  bookNameArr[39] = QString("3 Ezdráš");                                bookShortNameArr[39] = QString("3 Ezdráš");                        bookMinNameArr[39] = QString("3Ezd");//3Ezd
  bookNameArr[40] = QString("Tóbijáš");                                 bookShortNameArr[40] = QString("Tóbijáš");                         bookMinNameArr[40] = QString("Tób");//Tób
  bookNameArr[41] = QString("Júdit");                                   bookShortNameArr[41] = QString("Júdit");                           bookMinNameArr[41] = QString("Júdit");//Júd
  bookNameArr[42] = QString("Moudrost Šalomounova");                    bookShortNameArr[42] = QString("Moudrosti");                       bookMinNameArr[42] = QString("Mdr");//Mdr
  bookNameArr[43] = QString("Moudrost Ješuy, syna Sírachova");          bookShortNameArr[43] = QString("Sírachovec");                      bookMinNameArr[43] = QString("Sír");//Sír
  bookNameArr[44] = QString("List Jeremjášův");                         bookShortNameArr[44] = QString("List Jeremjášův");                 bookMinNameArr[44] = QString("LsJer");//LsJer
  bookNameArr[45] = QString("Báruch") ;                                 bookShortNameArr[45] = QString("Báruch");                          bookMinNameArr[45] = QString("Báruch");//Bár
  bookNameArr[46] = QString("1 Makabejská");                            bookShortNameArr[46] = QString("1 Makabejská");                    bookMinNameArr[46] = QString("1Mak");//1Mak
  bookNameArr[47] = QString("2 Makabejská");                            bookShortNameArr[47] = QString("2 Makabejská");                    bookMinNameArr[47] = QString("2Mak");//2Mak
  bookNameArr[48] = QString("3,4 Makabejská");                          bookShortNameArr[48] = QString("3,4 Makabejská");                  bookMinNameArr[48] = QString("3,4Mak");//3,4Mak
  bookNameArr[49] = QString("4 Ezdráš");                                bookShortNameArr[49] = QString("4 Ezdráš");                        bookMinNameArr[49] = QString("4Ezd");//4Ezd

  bookNameArr[50] = QString("Evangelium podle Matouše");                bookShortNameArr[50] = QString("Matouš");                          bookMinNameArr[50] = QString("Matouš");//Mt
  bookNameArr[51] = QString("Evangelium podle Marka");                  bookShortNameArr[51] = QString("Marek");                           bookMinNameArr[51] = QString("Marek");//Mk
  bookNameArr[52] = QString("Evangelium podle Lukáše");                 bookShortNameArr[52] = QString("Lukáš");                           bookMinNameArr[52] = QString("Lukáš");//Lk
  bookNameArr[53] = QString("Evangelium podle Jana");                   bookShortNameArr[53] = QString("Jan");                             bookMinNameArr[53] = QString("Jan");//Jan
  bookNameArr[54] = QString("Skutky apoštolů");                         bookShortNameArr[54] = QString("Skutky apoštolů");                 bookMinNameArr[54] = QString("Skut");//Sk

  bookNameArr[55] = QString("List Římanům");                            bookShortNameArr[55] = QString("Římanům");                         bookMinNameArr[55] = QString("Řím");//Řím
  bookNameArr[56] = QString("První list Korintským");                   bookShortNameArr[56] = QString("1 Korintským");                    bookMinNameArr[56] = QString("1Kor");//1Kor
  bookNameArr[57] = QString("Druhý list Korintským");                   bookShortNameArr[57] = QString("2 Korintským");                    bookMinNameArr[57] = QString("2Kor");//2Kor
  bookNameArr[58] = QString("List Galatským");                          bookShortNameArr[58] = QString("Galatským");                       bookMinNameArr[58] = QString("Galat");//Gal
  bookNameArr[59] = QString("List Efezským");                           bookShortNameArr[59] = QString("Efezským");                        bookMinNameArr[59] = QString("Efez");//Ef
  bookNameArr[60] = QString("List Filipským");                          bookShortNameArr[60] = QString("Filipským");                       bookMinNameArr[60] = QString("Filip");//Fp
  bookNameArr[61] = QString("List Koloským");                           bookShortNameArr[61] = QString("Koloským");                        bookMinNameArr[61] = QString("Kolos");//Kol
  bookNameArr[62] = QString("První list Tesalonickým");                 bookShortNameArr[62] = QString("1 Tesalonickým");                  bookMinNameArr[62] = QString("1Tes");//1Te
  bookNameArr[63] = QString("Druhý list Tesalonickým");                 bookShortNameArr[63] = QString("2 Tesalonickým");                  bookMinNameArr[63] = QString("2Tes");//2Te
  bookNameArr[64] = QString("První list Timoteovi");                    bookShortNameArr[64] = QString("1 Timoteovi");                     bookMinNameArr[64] = QString("1Tim");//1Tim
  bookNameArr[65] = QString("Druhý list Timoteovi");                    bookShortNameArr[65] = QString("2 Timoteovi");                     bookMinNameArr[65] = QString("2Tim");//2Tim
  bookNameArr[66] = QString("List Titovi");                             bookShortNameArr[66] = QString("Titovi");                          bookMinNameArr[66] = QString("Tit");//Tit
  bookNameArr[67] = QString("List Filemonovi");                         bookShortNameArr[67] = QString("Filemonovi");                      bookMinNameArr[67] = QString("Filem");//Flm
  bookNameArr[68] = QString("List Židům");                              bookShortNameArr[68] = QString("Židům");                           bookMinNameArr[68] = QString("Židům");//Žd

  bookNameArr[69] = QString("List Jakubův");                            bookShortNameArr[69] = QString("Jakubův");                         bookMinNameArr[69] = QString("Jakub");//Jk
  bookNameArr[70] = QString("1 list Petrův");                           bookShortNameArr[70] = QString("1 Petrův");                        bookMinNameArr[70] = QString("1Petr");//1Pt
  bookNameArr[71] = QString("2 list Petrův");                           bookShortNameArr[71] = QString("2 Petrův");                        bookMinNameArr[71] = QString("2Petr");//2Pt
  bookNameArr[72] = QString("1 list Janův");                            bookShortNameArr[72] = QString("1 Janův");                         bookMinNameArr[72] = QString("1Janův");//1J
  bookNameArr[73] = QString("2 list Janův");                            bookShortNameArr[73] = QString("2 Janův");                         bookMinNameArr[73] = QString("2Janův");//2J
  bookNameArr[74] = QString("3 list Janův");                            bookShortNameArr[74] = QString("3 Janův");                         bookMinNameArr[74] = QString("3Janův");//3J
  bookNameArr[75] = QString("List Judův");                              bookShortNameArr[75] = QString("Judův");                           bookMinNameArr[75] = QString("Judův");//Ju,Jd

  bookNameArr[76] = QString("Zjevení Janovo");                          bookShortNameArr[76] = QString("Zjevení");                         bookMinNameArr[76] = QString("Zjev");//Zj
}

// https://en.wikipedia.org/wiki/List_of_books_of_the_King_James_Version
// https://en.wikipedia.org/wiki/Books_of_the_Bible
// https://www.logos.com/support/windows/L3/book_abbreviations
void TrStrings::initBooksEnglish()
{
  bookNameArr[0]  = QString("Genesis");                                 bookShortNameArr[0]  = QString("Genesis");                         bookMinNameArr[0]  = QString("Gen");
  bookNameArr[1]  = QString("Exodus");                                  bookShortNameArr[1]  = QString("Exodus");                          bookMinNameArr[1]  = QString("Exod");
  bookNameArr[2]  = QString("Leviticus");                               bookShortNameArr[2]  = QString("Leviticus");                       bookMinNameArr[2]  = QString("Lev");
  bookNameArr[3]  = QString("Numbers");                                 bookShortNameArr[3]  = QString("Numbers");                         bookMinNameArr[3]  = QString("Num");
  bookNameArr[4]  = QString("Deuteronomy");                             bookShortNameArr[4]  = QString("Deuteronomy");                     bookMinNameArr[4]  = QString("Deut");
  bookNameArr[5]  = QString("Joshua");                                  bookShortNameArr[5]  = QString("Joshua");                          bookMinNameArr[5]  = QString("Josh");
  bookNameArr[6]  = QString("Judges");                                  bookShortNameArr[6]  = QString("Judges");                          bookMinNameArr[6]  = QString("Judg");
  bookNameArr[7]  = QString("Ruth");                                    bookShortNameArr[7]  = QString("Ruth");                            bookMinNameArr[7]  = QString("Ruth");
  bookNameArr[8]  = QString("1 Samuel");                                bookShortNameArr[8]  = QString("1 Samuel");                        bookMinNameArr[8]  = QString("1Sam");
  bookNameArr[9]  = QString("2 Samuel");                                bookShortNameArr[9]  = QString("2 Samuel");                        bookMinNameArr[9]  = QString("2Sam");
  bookNameArr[10] = QString("1 Kings");                                 bookShortNameArr[10] = QString("1 Kings");                         bookMinNameArr[10] = QString("1Kgs");
  bookNameArr[11] = QString("2 Kings");                                 bookShortNameArr[11] = QString("2 Kings");                         bookMinNameArr[11] = QString("2Kgs");
  bookNameArr[12] = QString("1 Chronicles");                            bookShortNameArr[12] = QString("1 Chronicles");                    bookMinNameArr[12] = QString("1Chron");
  bookNameArr[13] = QString("2 Chronicles");                            bookShortNameArr[13] = QString("2 Chronicles");                    bookMinNameArr[13] = QString("2Chron");
  bookNameArr[14] = QString("Ezra");                                    bookShortNameArr[14] = QString("Ezra");                            bookMinNameArr[14] = QString("Ezra");
  bookNameArr[15] = QString("Nehemiah");                                bookShortNameArr[15] = QString("Nehemiah");                        bookMinNameArr[15] = QString("Neh");
  bookNameArr[16] = QString("Esther");                                  bookShortNameArr[16] = QString("Esther");                          bookMinNameArr[16] = QString("Esth");
  bookNameArr[17] = QString("Job");                                     bookShortNameArr[17] = QString("Job");                             bookMinNameArr[17] = QString("Job");
  bookNameArr[18] = QString("Psalms");                                  bookShortNameArr[18] = QString("Psalms");                          bookMinNameArr[18] = QString("Ps");
  bookNameArr[19] = QString("Proverbs");                                bookShortNameArr[19] = QString("Proverbs");                        bookMinNameArr[19] = QString("Prov");
  bookNameArr[20] = QString("Ecclesiastes");                            bookShortNameArr[20] = QString("Ecclesiastes");                    bookMinNameArr[20] = QString("Ecc");
  bookNameArr[21] = QString("Song of Solomon");                         bookShortNameArr[21] = QString("Song of Solomon");                 bookMinNameArr[21] = QString("Song");
  bookNameArr[22] = QString("Isaiah");                                  bookShortNameArr[22] = QString("Isaiah");                          bookMinNameArr[22] = QString("Isa");
  bookNameArr[23] = QString("Jeremiah");                                bookShortNameArr[23] = QString("Jeremiah");                        bookMinNameArr[23] = QString("Jer");
  bookNameArr[24] = QString("Lamentations");                            bookShortNameArr[24] = QString("Lamentations");                    bookMinNameArr[24] = QString("Lam");
  bookNameArr[25] = QString("Ezekiel");                                 bookShortNameArr[25] = QString("Ezekiel");                         bookMinNameArr[25] = QString("Ezek");
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Dan");
  bookNameArr[27] = QString("Hosea");                                   bookShortNameArr[27] = QString("Hosea");                           bookMinNameArr[27] = QString("Hos");
  bookNameArr[28] = QString("Joel");                                    bookShortNameArr[28] = QString("Joel");                            bookMinNameArr[28] = QString("Joel");
  bookNameArr[29] = QString("Amos");                                    bookShortNameArr[29] = QString("Amos");                            bookMinNameArr[29] = QString("Amos");
  bookNameArr[30] = QString("Obadiah");                                 bookShortNameArr[30] = QString("Obadiah");                         bookMinNameArr[30] = QString("Obad");
  bookNameArr[31] = QString("Jonah");                                   bookShortNameArr[31] = QString("Jonah");                           bookMinNameArr[31] = QString("Jonah");
  bookNameArr[32] = QString("Micah");                                   bookShortNameArr[32] = QString("Micah");                           bookMinNameArr[32] = QString("Micah");
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nahum");
  bookNameArr[34] = QString("Habakkuk");                                bookShortNameArr[34] = QString("Habakkuk");                        bookMinNameArr[34] = QString("Hab");
  bookNameArr[35] = QString("Zephaniah");                               bookShortNameArr[35] = QString("Zephaniah");                       bookMinNameArr[35] = QString("Zeph");
  bookNameArr[36] = QString("Haggai");                                  bookShortNameArr[36] = QString("Haggai");                          bookMinNameArr[36] = QString("Hag");
  bookNameArr[37] = QString("Zechariah");                               bookShortNameArr[37] = QString("Zechariah");                       bookMinNameArr[37] = QString("Zech");
  bookNameArr[38] = QString("Malachi");                                 bookShortNameArr[38] = QString("Malachi");                         bookMinNameArr[38] = QString("Mal");

  bookNameArr[39] = QString("1 Esdras");                                bookShortNameArr[39] = QString("1 Esdras");                        bookMinNameArr[39] = QString("1Esd");
  bookNameArr[40] = QString("Tobit");                                   bookShortNameArr[40] = QString("Tobit");                           bookMinNameArr[40] = QString("Tobit");
  bookNameArr[41] = QString("Judith");                                  bookShortNameArr[41] = QString("Judith");                          bookMinNameArr[41] = QString("Judith");
  bookNameArr[42] = QString("Wisdom of Solomon");                       bookShortNameArr[42] = QString("Wisdom");                          bookMinNameArr[42] = QString("Wisdom");
  bookNameArr[43] = QString("Wisdom of Jesus the son of Sirach");       bookShortNameArr[43] = QString("Sirach"); /*Ecclesiasticus*/       bookMinNameArr[43] = QString("Sirach");
  bookNameArr[44] = QString("Epistle of Jeremiah"); /*Letter of Jeremiah*/bookShortNameArr[44] = QString("Epistle of Jeremiah");           bookMinNameArr[44] = QString("EpJer");//LetJer
  bookNameArr[45] = QString("Baruch");                                  bookShortNameArr[45] = QString("Baruch");                          bookMinNameArr[45] = QString("Baruch");
  bookNameArr[46] = QString("1 Maccabees");                             bookShortNameArr[46] = QString("1 Maccabees");                     bookMinNameArr[46] = QString("1Macc");
  bookNameArr[47] = QString("2 Maccabees");                             bookShortNameArr[47] = QString("2 Maccabees");                     bookMinNameArr[47] = QString("2Macc");
  bookNameArr[48] = QString("3,4 Maccabees");                           bookShortNameArr[48] = QString("3,4 Maccabees");                   bookMinNameArr[48] = QString("3,4Macc");
  bookNameArr[49] = QString("2 Esdras");                                bookShortNameArr[49] = QString("2 Esdras");                        bookMinNameArr[49] = QString("2Esd");

  bookNameArr[50] = QString("The Gospel According to St. Matthew");     bookShortNameArr[50] = QString("Matthew");                         bookMinNameArr[50] = QString("Matt");
  bookNameArr[51] = QString("The Gospel According to St. Mark");        bookShortNameArr[51] = QString("Mark");                            bookMinNameArr[51] = QString("Mark");
  bookNameArr[52] = QString("The Gospel According to St. Luke");        bookShortNameArr[52] = QString("Luke");                            bookMinNameArr[52] = QString("Luke");
  bookNameArr[53] = QString("The Gospel According to St. John");        bookShortNameArr[53] = QString("John");                            bookMinNameArr[53] = QString("John");
  bookNameArr[54] = QString("The Acts of the Apostles");                bookShortNameArr[54] = QString("Acts");                            bookMinNameArr[54] = QString("Acts");

  bookNameArr[55] = QString("Romans");                                  bookShortNameArr[55] = QString("Romans");                          bookMinNameArr[55] = QString("Rom");
  bookNameArr[56] = QString("1 Corinthians");                           bookShortNameArr[56] = QString("1 Corinthians");                   bookMinNameArr[56] = QString("1Cor");
  bookNameArr[57] = QString("2 Corinthians");                           bookShortNameArr[57] = QString("2 Corinthians");                   bookMinNameArr[57] = QString("2Cor");
  bookNameArr[58] = QString("Galatians");                               bookShortNameArr[58] = QString("Galatians");                       bookMinNameArr[58] = QString("Gal");
  bookNameArr[59] = QString("Ephesians");                               bookShortNameArr[59] = QString("Ephesians");                       bookMinNameArr[59] = QString("Eph");
  bookNameArr[60] = QString("Philippians");                             bookShortNameArr[60] = QString("Philippians");                     bookMinNameArr[60] = QString("Phil");
  bookNameArr[61] = QString("Colossians");                              bookShortNameArr[61] = QString("Colossians");                      bookMinNameArr[61] = QString("Col");
  bookNameArr[62] = QString("1 Thessalonians");                         bookShortNameArr[62] = QString("1 Thessalonians");                 bookMinNameArr[62] = QString("1Thess");
  bookNameArr[63] = QString("2 Thessalonians");                         bookShortNameArr[63] = QString("2 Thessalonians");                 bookMinNameArr[63] = QString("2Thess");
  bookNameArr[64] = QString("1 Timothy");                               bookShortNameArr[64] = QString("1 Timothy");                       bookMinNameArr[64] = QString("1Tim");
  bookNameArr[65] = QString("2 Timothy");                               bookShortNameArr[65] = QString("2 Timothy");                       bookMinNameArr[65] = QString("2Tim");
  bookNameArr[66] = QString("Titus");                                   bookShortNameArr[66] = QString("Titus");                           bookMinNameArr[66] = QString("Titus");
  bookNameArr[67] = QString("Philemon");                                bookShortNameArr[67] = QString("Philemon");                        bookMinNameArr[67] = QString("Phlm");
  bookNameArr[68] = QString("Hebrews");                                 bookShortNameArr[68] = QString("Hebrews");                         bookMinNameArr[68] = QString("Heb");

  bookNameArr[69] = QString("James");                                   bookShortNameArr[69] = QString("James");                           bookMinNameArr[69] = QString("Jas");
  bookNameArr[70] = QString("1 Peter");                                 bookShortNameArr[70] = QString("1 Peter");                         bookMinNameArr[70] = QString("1Pet");
  bookNameArr[71] = QString("2 Peter");                                 bookShortNameArr[71] = QString("2 Peter");                         bookMinNameArr[71] = QString("2Pet");
  bookNameArr[72] = QString("1 John");                                  bookShortNameArr[72] = QString("1 John");                          bookMinNameArr[72] = QString("1John");
  bookNameArr[73] = QString("2 John");                                  bookShortNameArr[73] = QString("2 John");                          bookMinNameArr[73] = QString("2John");
  bookNameArr[74] = QString("3 John");                                  bookShortNameArr[74] = QString("3 John");                          bookMinNameArr[74] = QString("3John");
  bookNameArr[75] = QString("Jude");                                    bookShortNameArr[75] = QString("Jude");                            bookMinNameArr[75] = QString("Jude");

  bookNameArr[76] = QString("The Revelation of St. John");              bookShortNameArr[76] = QString("Revelation");                      bookMinNameArr[76] = QString("Rev");
}

// https://fr.wikipedia.org/wiki/Bible
// https://fr.wikipedia.org/wiki/Ancien_Testament
// https://fr.wikipedia.org/wiki/Nouveau_Testament
// https://fr.wikipedia.org/wiki/Liste_des_livres_de_la_Bible
// https://fr.wikipedia.org/wiki/Apocryphes_bibliques
// https://fr.wikipedia.org/wiki/Modèle:Abréviation_livre_de_la_Bible
// http://www.orthotypographie.fr/volume-I/lacroux-bible.pdf
void TrStrings::initBooksFrench()
{
  bookNameArr[0]  = QString("Genèse");                                  bookShortNameArr[0]  = QString("Genèse");                          bookMinNameArr[0]  = QString("Gen");//Gn
  bookNameArr[1]  = QString("Exode");                                   bookShortNameArr[1]  = QString("Exode");                           bookMinNameArr[1]  = QString("Ex");//Ex
  bookNameArr[2]  = QString("Lévitique");                               bookShortNameArr[2]  = QString("Lévitique");                       bookMinNameArr[2]  = QString("Lév");//Lv
  bookNameArr[3]  = QString("Nombres");                                 bookShortNameArr[3]  = QString("Nombres");                         bookMinNameArr[3]  = QString("Nomb");//Nb
  bookNameArr[4]  = QString("Deutéronome");                             bookShortNameArr[4]  = QString("Deutéronome");                     bookMinNameArr[4]  = QString("Deut");//Dt
  bookNameArr[5]  = QString("Josué");                                   bookShortNameArr[5]  = QString("Josué");                           bookMinNameArr[5]  = QString("Jos");//Js
  bookNameArr[6]  = QString("Juges");                                   bookShortNameArr[6]  = QString("Juges");                           bookMinNameArr[6]  = QString("Juges");//Jg
  bookNameArr[7]  = QString("Ruth");                                    bookShortNameArr[7]  = QString("Ruth");                            bookMinNameArr[7]  = QString("Ruth");//Rt
  bookNameArr[8]  = QString("1 Samuel");                                bookShortNameArr[8]  = QString("1 Samuel");                        bookMinNameArr[8]  = QString("1Sam");//1S
  bookNameArr[9]  = QString("2 Samuel");                                bookShortNameArr[9]  = QString("2 Samuel");                        bookMinNameArr[9]  = QString("2Sam");//2S
  bookNameArr[10] = QString("1 Rois");                                  bookShortNameArr[10] = QString("1 Rois");                          bookMinNameArr[10] = QString("1Rois");//1R
  bookNameArr[11] = QString("2 Rois");                                  bookShortNameArr[11] = QString("2 Rois");                          bookMinNameArr[11] = QString("2Rois");//2R
  bookNameArr[12] = QString("1 Chroniques");                            bookShortNameArr[12] = QString("1 Chroniques");                    bookMinNameArr[12] = QString("1Chron");//1Ch
  bookNameArr[13] = QString("2 Chroniques");                            bookShortNameArr[13] = QString("2 Chroniques");                    bookMinNameArr[13] = QString("2Chron");//2Ch
  bookNameArr[14] = QString("Esdras");                                  bookShortNameArr[14] = QString("Esdras");                          bookMinNameArr[14] = QString("Esd");//Esd
  bookNameArr[15] = QString("Néhémie");                                 bookShortNameArr[15] = QString("Néhémie");                         bookMinNameArr[15] = QString("Néh");//Ne
  bookNameArr[16] = QString("Esther");                                  bookShortNameArr[16] = QString("Esther");                          bookMinNameArr[16] = QString("Esth");//Est
  bookNameArr[17] = QString("Job");                                     bookShortNameArr[17] = QString("Job");                             bookMinNameArr[17] = QString("Job");//Jb
  bookNameArr[18] = QString("Psaumes");                                 bookShortNameArr[18] = QString("Psaumes");                         bookMinNameArr[18] = QString("Ps");//Ps
  bookNameArr[19] = QString("Proverbes");                               bookShortNameArr[19] = QString("Proverbes");                       bookMinNameArr[19] = QString("Prov");//Pr
  bookNameArr[20] = QString("Ecclésiaste");                             bookShortNameArr[20] = QString("Ecclésiaste");                     bookMinNameArr[20] = QString("Eccl");//Ec
  bookNameArr[21] = QString("Cantique des Cantiques");                  bookShortNameArr[21] = QString("Cantique");                        bookMinNameArr[21] = QString("Cant");//Ct
  bookNameArr[22] = QString("Ésaïe");                                   bookShortNameArr[22] = QString("Ésaïe");                           bookMinNameArr[22] = QString("És");//Es
  bookNameArr[23] = QString("Jérémie");                                 bookShortNameArr[23] = QString("Jérémie");                         bookMinNameArr[23] = QString("Jér");//Jr
  bookNameArr[24] = QString("Lamentations");                            bookShortNameArr[24] = QString("Lamentations");                    bookMinNameArr[24] = QString("Lam");//La
  bookNameArr[25] = QString("Ézéchiel");                                bookShortNameArr[25] = QString("Ézéchiel");                        bookMinNameArr[25] = QString("Ézéc");//Ez
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Dan");//Da
  bookNameArr[27] = QString("Osée");                                    bookShortNameArr[27] = QString("Osée");                            bookMinNameArr[27] = QString("Osée");//Os
  bookNameArr[28] = QString("Joël");                                    bookShortNameArr[28] = QString("Joël");                            bookMinNameArr[28] = QString("Joël");//Jl
  bookNameArr[29] = QString("Amos");                                    bookShortNameArr[29] = QString("Amos");                            bookMinNameArr[29] = QString("Amos");//Am
  bookNameArr[30] = QString("Abdias");                                  bookShortNameArr[30] = QString("Abdias");                          bookMinNameArr[30] = QString("Abd");//Ab
  bookNameArr[31] = QString("Jonas");                                   bookShortNameArr[31] = QString("Jonas");                           bookMinNameArr[31] = QString("Jonas");//Jon
  bookNameArr[32] = QString("Michée");                                  bookShortNameArr[32] = QString("Michée");                          bookMinNameArr[32] = QString("Mich");//Mi
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nahum");//Na
  bookNameArr[34] = QString("Habacuc");                                 bookShortNameArr[34] = QString("Habacuc");                         bookMinNameArr[34] = QString("Hab");//Ha
  bookNameArr[35] = QString("Sophonie");                                bookShortNameArr[35] = QString("Sophonie");                        bookMinNameArr[35] = QString("Soph");//So
  bookNameArr[36] = QString("Aggée");                                   bookShortNameArr[36] = QString("Aggée");                           bookMinNameArr[36] = QString("Agg");//Ag
  bookNameArr[37] = QString("Zacharie");                                bookShortNameArr[37] = QString("Zacharie");                        bookMinNameArr[37] = QString("Zach");//Za
  bookNameArr[38] = QString("Malachie");                                bookShortNameArr[38] = QString("Malachie");                        bookMinNameArr[38] = QString("Mal");//Ma

  bookNameArr[39] = QString("1 Esdras");                                bookShortNameArr[39] = QString("1 Esdras");                        bookMinNameArr[39] = QString("1Esd");//1Esd
  bookNameArr[40] = QString("Tobit");                                   bookShortNameArr[40] = QString("Tobit");                           bookMinNameArr[40] = QString("Tobit");//Tb
  bookNameArr[41] = QString("Judith");                                  bookShortNameArr[41] = QString("Judith");                          bookMinNameArr[41] = QString("Judith");//Jdt
  bookNameArr[42] = QString("Sagesse de Salomon");                      bookShortNameArr[42] = QString("Sagesse");                         bookMinNameArr[42] = QString("Sag");//Sg
  bookNameArr[43] = QString("Sagesse de Jésus Ben Sira");               bookShortNameArr[43] = QString("Siracide"); /*Ecclésiastique*/     bookMinNameArr[43] = QString("Sir");//Si
  bookNameArr[44] = QString("Epître de Jérémie");                       bookShortNameArr[44] = QString("Epître de Jérémie");               bookMinNameArr[44] = QString("EpJér");//EpJr
  bookNameArr[45] = QString("Baruch");                                  bookShortNameArr[45] = QString("Baruch");                          bookMinNameArr[45] = QString("Baruch");//Ba
  bookNameArr[46] = QString("1 Maccabées");                             bookShortNameArr[46] = QString("1 Maccabées");                     bookMinNameArr[46] = QString("1Macc");//1M
  bookNameArr[47] = QString("2 Maccabées");                             bookShortNameArr[47] = QString("2 Maccabées");                     bookMinNameArr[47] = QString("2Macc");//2M
  bookNameArr[48] = QString("3,4 Maccabées");                           bookShortNameArr[48] = QString("3,4 Maccabées");                   bookMinNameArr[48] = QString("3,4Macc");//3,4M
  bookNameArr[49] = QString("2 Esdras");                                bookShortNameArr[49] = QString("2 Esdras");                        bookMinNameArr[49] = QString("2Esd");//2Esd

  bookNameArr[50] = QString("Évangile selon Matthieu");                 bookShortNameArr[50] = QString("Matthieu");                        bookMinNameArr[50] = QString("Matt");//Mt
  bookNameArr[51] = QString("Évangile selon Marc");                     bookShortNameArr[51] = QString("Marc");                            bookMinNameArr[51] = QString("Marc");//Mc
  bookNameArr[52] = QString("Évangile selon Luc");                      bookShortNameArr[52] = QString("Luc");                             bookMinNameArr[52] = QString("Luc");//Lc
  bookNameArr[53] = QString("Évangile selon Jean");                     bookShortNameArr[53] = QString("Jean");                            bookMinNameArr[53] = QString("Jean");//Jn
  bookNameArr[54] = QString("Actes des Apôtres");                       bookShortNameArr[54] = QString("Actes");                           bookMinNameArr[54] = QString("Actes");//Ac

  bookNameArr[55] = QString("Épître aux Romains");                      bookShortNameArr[55] = QString("Romains");                         bookMinNameArr[55] = QString("Rom");//Rm
  bookNameArr[56] = QString("Première épître aux Corinthiens");         bookShortNameArr[56] = QString("1 Corinthiens");                   bookMinNameArr[56] = QString("1Cor");//1Co
  bookNameArr[57] = QString("Deuxième épître aux Corinthiens");         bookShortNameArr[57] = QString("2 Corinthiens");                   bookMinNameArr[57] = QString("2Cor");//2Co
  bookNameArr[58] = QString("Épître aux Galates");                      bookShortNameArr[58] = QString("Galates");                         bookMinNameArr[58] = QString("Gal");//Ga
  bookNameArr[59] = QString("Épître aux Éphésiens");                    bookShortNameArr[59] = QString("Éphésiens");                       bookMinNameArr[59] = QString("Éph");//Ep
  bookNameArr[60] = QString("Épître aux Philippiens");                  bookShortNameArr[60] = QString("Philippiens");                     bookMinNameArr[60] = QString("Phil");//Ph
  bookNameArr[61] = QString("Épître aux Colossiens");                   bookShortNameArr[61] = QString("Colossiens");                      bookMinNameArr[61] = QString("Col");//Col
  bookNameArr[62] = QString("Première épître aux Thessaloniciens");     bookShortNameArr[62] = QString("1 Thessaloniciens");               bookMinNameArr[62] = QString("1Thess");//1Th
  bookNameArr[63] = QString("Deuxième épître aux Thessaloniciens");     bookShortNameArr[63] = QString("2 Thessaloniciens");               bookMinNameArr[63] = QString("2Thess");//2Th
  bookNameArr[64] = QString("Première épître à Timothée");              bookShortNameArr[64] = QString("1 Timothée");                      bookMinNameArr[64] = QString("1Tim");//1Ti
  bookNameArr[65] = QString("Deuxième épître à Timothée");              bookShortNameArr[65] = QString("2 Timothée");                      bookMinNameArr[65] = QString("2Tim");//2Ti
  bookNameArr[66] = QString("Épître à Tite");                           bookShortNameArr[66] = QString("Tite");                            bookMinNameArr[66] = QString("Tite");//Tt
  bookNameArr[67] = QString("Épître à Philémon");                       bookShortNameArr[67] = QString("Philémon");                        bookMinNameArr[67] = QString("Phm");//Phm
  bookNameArr[68] = QString("Épître aux Hébreux");                      bookShortNameArr[68] = QString("Hébreux");                         bookMinNameArr[68] = QString("Hébr");//He

  bookNameArr[69] = QString("Épître de Jacques");                       bookShortNameArr[69] = QString("Jacques");                         bookMinNameArr[69] = QString("Jacq");//Jc
  bookNameArr[70] = QString("Première épître de Pierre");               bookShortNameArr[70] = QString("1 Pierre");                        bookMinNameArr[70] = QString("1Pi");//1P
  bookNameArr[71] = QString("Deuxième épître de Pierre");               bookShortNameArr[71] = QString("2 Pierre");                        bookMinNameArr[71] = QString("2Pi");//2P
  bookNameArr[72] = QString("Première épître de Jean");                 bookShortNameArr[72] = QString("1 Jean");                          bookMinNameArr[72] = QString("1Jean");//1Jn
  bookNameArr[73] = QString("Deuxième épître de Jean");                 bookShortNameArr[73] = QString("2 Jean");                          bookMinNameArr[73] = QString("2Jean");//2Jn
  bookNameArr[74] = QString("Troisième épître de Jean");                bookShortNameArr[74] = QString("3 Jean");                          bookMinNameArr[74] = QString("3Jean");//3Jn
  bookNameArr[75] = QString("Épître de Jude");                          bookShortNameArr[75] = QString("Jude");                            bookMinNameArr[75] = QString("Jude");//Jd

  bookNameArr[76] = QString("Apocalypse de Jean");                      bookShortNameArr[76] = QString("Apocalypse");                      bookMinNameArr[76] = QString("Apoc");//Ap
}

// https://de.wikipedia.org/wiki/Liste_biblischer_B%C3%BCcher
// https://de.wikipedia.org/wiki/Apokryphen
void TrStrings::initBooksGerman()
{
  bookNameArr[0]  = QString("Genesis");       /*1 Mose*/                bookShortNameArr[0]  = QString("Genesis");                         bookMinNameArr[0]  = QString("Gen");/*1Mos*/
  bookNameArr[1]  = QString("Exodus");        /*2 Mose*/                bookShortNameArr[1]  = QString("Exodus");                          bookMinNameArr[1]  = QString("Ex"); /*2Mos*/
  bookNameArr[2]  = QString("Levitikus");     /*3 Mose*/                bookShortNameArr[2]  = QString("Levitikus");                       bookMinNameArr[2]  = QString("Lev");/*3Mos*/
  bookNameArr[3]  = QString("Numeri");        /*4 Mose*/                bookShortNameArr[3]  = QString("Numeri");                          bookMinNameArr[3]  = QString("Num");/*4Mos*/
  bookNameArr[4]  = QString("Deuteronomium"); /*5 Mose*/                bookShortNameArr[4]  = QString("Deuteronomium");                   bookMinNameArr[4]  = QString("Dtn");/*5Mos*/
  bookNameArr[5]  = QString("Josua");                                   bookShortNameArr[5]  = QString("Josua");                           bookMinNameArr[5]  = QString("Jos");
  bookNameArr[6]  = QString("Richter");                                 bookShortNameArr[6]  = QString("Richter");                         bookMinNameArr[6]  = QString("Ri");
  bookNameArr[7]  = QString("Rut");                                     bookShortNameArr[7]  = QString("Rut");                             bookMinNameArr[7]  = QString("Rut");
  bookNameArr[8]  = QString("1 Samuel");                                bookShortNameArr[8]  = QString("1 Samuel");                        bookMinNameArr[8]  = QString("1Sam");
  bookNameArr[9]  = QString("2 Samuel");                                bookShortNameArr[9]  = QString("2 Samuel");                        bookMinNameArr[9]  = QString("2Sam");
  bookNameArr[10] = QString("1 Könige");                                bookShortNameArr[10] = QString("1 Könige");                        bookMinNameArr[10] = QString("1Kön");
  bookNameArr[11] = QString("2 Könige");                                bookShortNameArr[11] = QString("2 Könige");                        bookMinNameArr[11] = QString("2Kön");
  bookNameArr[12] = QString("1 Chronik");                               bookShortNameArr[12] = QString("1 Chronik");                       bookMinNameArr[12] = QString("1Chr");
  bookNameArr[13] = QString("2 Chronik");                               bookShortNameArr[13] = QString("2 Chronik");                       bookMinNameArr[13] = QString("2Chr");
  bookNameArr[14] = QString("Esra");                                    bookShortNameArr[14] = QString("Esra");                            bookMinNameArr[14] = QString("Esra");
  bookNameArr[15] = QString("Nehemia");                                 bookShortNameArr[15] = QString("Nehemia");                         bookMinNameArr[15] = QString("Neh");
  bookNameArr[16] = QString("Ester");                                   bookShortNameArr[16] = QString("Ester");                           bookMinNameArr[16] = QString("Est");
  bookNameArr[17] = QString("Ijob"); /*Hiob*/ /*Job*/                   bookShortNameArr[17] = QString("Ijob");                            bookMinNameArr[17] = QString("Ijob");/*Hi*/
  bookNameArr[18] = QString("Psalmen");                                 bookShortNameArr[18] = QString("Psalmen");                         bookMinNameArr[18] = QString("Ps");
  bookNameArr[19] = QString("Sprichwörter"); /*Sprüche Salomos*/        bookShortNameArr[19] = QString("Sprichwörter"); /*Sprüche*/        bookMinNameArr[19] = QString("Spr");
  bookNameArr[20] = QString("Kohelet"); /*Prediger*/                    bookShortNameArr[20] = QString("Kohelet");                         bookMinNameArr[20] = QString("Koh");/*Pred*/
  bookNameArr[21] = QString("Hoheslied"); /*Hohes Lied*/                bookShortNameArr[21] = QString("Hoheslied");                       bookMinNameArr[21] = QString("Hld");
  bookNameArr[22] = QString("Jesaja");                                  bookShortNameArr[22] = QString("Jesaja");                          bookMinNameArr[22] = QString("Jes");/*Is*/
  bookNameArr[23] = QString("Jeremia");                                 bookShortNameArr[23] = QString("Jeremia");                         bookMinNameArr[23] = QString("Jer");
  bookNameArr[24] = QString("Klagelieder Jeremias");                    bookShortNameArr[24] = QString("Klagelieder");                     bookMinNameArr[24] = QString("Klgl");
  bookNameArr[25] = QString("Ezechiel"); /*Hesekiel*/                   bookShortNameArr[25] = QString("Ezechiel");                        bookMinNameArr[25] = QString("Ez");/*Hes*/
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Dan");
  bookNameArr[27] = QString("Hosea");                                   bookShortNameArr[27] = QString("Hosea");                           bookMinNameArr[27] = QString("Hos");
  bookNameArr[28] = QString("Joel");                                    bookShortNameArr[28] = QString("Joel");                            bookMinNameArr[28] = QString("Joel");
  bookNameArr[29] = QString("Amos");                                    bookShortNameArr[29] = QString("Amos");                            bookMinNameArr[29] = QString("Am");
  bookNameArr[30] = QString("Obadja");                                  bookShortNameArr[30] = QString("Obadja");                          bookMinNameArr[30] = QString("Obd");
  bookNameArr[31] = QString("Jona");                                    bookShortNameArr[31] = QString("Jona");                            bookMinNameArr[31] = QString("Jona");
  bookNameArr[32] = QString("Micha");                                   bookShortNameArr[32] = QString("Micha");                           bookMinNameArr[32] = QString("Mi");
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nah");
  bookNameArr[34] = QString("Habakuk"); /*Habakkuk*/                    bookShortNameArr[34] = QString("Habakuk");                         bookMinNameArr[34] = QString("Hab");
  bookNameArr[35] = QString("Zefanja"); /*Zephanja*/                    bookShortNameArr[35] = QString("Zefanja");                         bookMinNameArr[35] = QString("Zef");
  bookNameArr[36] = QString("Haggai");                                  bookShortNameArr[36] = QString("Haggai");                          bookMinNameArr[36] = QString("Hag");
  bookNameArr[37] = QString("Sacharja");                                bookShortNameArr[37] = QString("Sacharja");                        bookMinNameArr[37] = QString("Sach");
  bookNameArr[38] = QString("Maleachi");                                bookShortNameArr[38] = QString("Maleachi");                        bookMinNameArr[38] = QString("Mal");

  bookNameArr[39] = QString("3 Esra");                                  bookShortNameArr[39] = QString("3 Esra");                          bookMinNameArr[39] = QString("3Esra");
  bookNameArr[40] = QString("Tobit");                                   bookShortNameArr[40] = QString("Tobit");                           bookMinNameArr[40] = QString("Tobit");//Tob
  bookNameArr[41] = QString("Judit");                                   bookShortNameArr[41] = QString("Judit");                           bookMinNameArr[41] = QString("Judit");
  bookNameArr[42] = QString("Weisheit Salomos");                        bookShortNameArr[42] = QString("Weisheit Salomos");                bookMinNameArr[42] = QString("Weish");
  bookNameArr[43] = QString("Jesus Sirach");                            bookShortNameArr[43] = QString("Jesus Sirach");                    bookMinNameArr[43] = QString("Sirach");//Sir
  bookNameArr[44] = QString("Brief des Jeremia");                       bookShortNameArr[44] = QString("Brief des Jeremia");               bookMinNameArr[44] = QString("BrJer");
  bookNameArr[45] = QString("Baruch");                                  bookShortNameArr[45] = QString("Baruch");                          bookMinNameArr[45] = QString("Baruch");//Bar
  bookNameArr[46] = QString("1 Makkabäer");                             bookShortNameArr[46] = QString("1 Makkabäer");                     bookMinNameArr[46] = QString("1Makk");
  bookNameArr[47] = QString("2 Makkabäer");                             bookShortNameArr[47] = QString("2 Makkabäer");                     bookMinNameArr[47] = QString("2Makk");
  bookNameArr[48] = QString("3,4 Makkabäer");                           bookShortNameArr[48] = QString("3,4 Makkabäer");                   bookMinNameArr[48] = QString("3,4Makk");
  bookNameArr[49] = QString("4 Esra");                                  bookShortNameArr[49] = QString("4 Esra");                          bookMinNameArr[49] = QString("4Esra");

  bookNameArr[50] = QString("Matthäus");                                bookShortNameArr[50] = QString("Matthäus");                        bookMinNameArr[50] = QString("Mt");
  bookNameArr[51] = QString("Markus");                                  bookShortNameArr[51] = QString("Markus");                          bookMinNameArr[51] = QString("Mk");
  bookNameArr[52] = QString("Lukas");                                   bookShortNameArr[52] = QString("Lukas");                           bookMinNameArr[52] = QString("Lk");
  bookNameArr[53] = QString("Johannes");                                bookShortNameArr[53] = QString("Johannes");                        bookMinNameArr[53] = QString("Joh");
  bookNameArr[54] = QString("Apostelgeschichte");                       bookShortNameArr[54] = QString("Apostelgeschichte");               bookMinNameArr[54] = QString("Apg");

  bookNameArr[55] = QString("Römer");                                   bookShortNameArr[55] = QString("Römer");                           bookMinNameArr[55] = QString("Röm");
  bookNameArr[56] = QString("1 Korinther");                             bookShortNameArr[56] = QString("1 Korinther");                     bookMinNameArr[56] = QString("1Kor");
  bookNameArr[57] = QString("2 Korinther");                             bookShortNameArr[57] = QString("2 Korinther");                     bookMinNameArr[57] = QString("2Kor");
  bookNameArr[58] = QString("Galater");                                 bookShortNameArr[58] = QString("Galater");                         bookMinNameArr[58] = QString("Gal");
  bookNameArr[59] = QString("Epheser");                                 bookShortNameArr[59] = QString("Epheser");                         bookMinNameArr[59] = QString("Eph");
  bookNameArr[60] = QString("Philipper");                               bookShortNameArr[60] = QString("Philipper");                       bookMinNameArr[60] = QString("Phil");
  bookNameArr[61] = QString("Kolosser");                                bookShortNameArr[61] = QString("Kolosser");                        bookMinNameArr[61] = QString("Kol");
  bookNameArr[62] = QString("1 Thessalonicher");                        bookShortNameArr[62] = QString("1 Thessalonicher");                bookMinNameArr[62] = QString("1Thess");
  bookNameArr[63] = QString("2 Thessalonicher");                        bookShortNameArr[63] = QString("2 Thessalonicher");                bookMinNameArr[63] = QString("2Thess");
  bookNameArr[64] = QString("1 Timotheus");                             bookShortNameArr[64] = QString("1 Timotheus");                     bookMinNameArr[64] = QString("1Tim");
  bookNameArr[65] = QString("2 Timotheus");                             bookShortNameArr[65] = QString("2 Timotheus");                     bookMinNameArr[65] = QString("2Tim");
  bookNameArr[66] = QString("Titus");                                   bookShortNameArr[66] = QString("Titus");                           bookMinNameArr[66] = QString("Tit");
  bookNameArr[67] = QString("Philemon");                                bookShortNameArr[67] = QString("Philemon");                        bookMinNameArr[67] = QString("Phlm");
  bookNameArr[68] = QString("Hebräer");                                 bookShortNameArr[68] = QString("Hebräer");                         bookMinNameArr[68] = QString("Hebr");

  bookNameArr[69] = QString("Jakobus");                                 bookShortNameArr[69] = QString("Jakobus");                         bookMinNameArr[69] = QString("Jak");
  bookNameArr[70] = QString("1 Petrus");                                bookShortNameArr[70] = QString("1 Petrus");                        bookMinNameArr[70] = QString("1Petr");
  bookNameArr[71] = QString("2 Petrus");                                bookShortNameArr[71] = QString("2 Petrus");                        bookMinNameArr[71] = QString("2Petr");
  bookNameArr[72] = QString("1 Johannes");                              bookShortNameArr[72] = QString("1 Johannes");                      bookMinNameArr[72] = QString("1Joh");
  bookNameArr[73] = QString("2 Johannes");                              bookShortNameArr[73] = QString("2 Johannes");                      bookMinNameArr[73] = QString("2Joh");
  bookNameArr[74] = QString("3 Johannes");                              bookShortNameArr[74] = QString("3 Johannes");                      bookMinNameArr[74] = QString("3Joh");
  bookNameArr[75] = QString("Judas");                                   bookShortNameArr[75] = QString("Judas");                           bookMinNameArr[75] = QString("Jud");

  bookNameArr[76] = QString("Offenbarung");                             bookShortNameArr[76] = QString("Offenbarung");                     bookMinNameArr[76] = QString("Offb");
}

// https://hu.wikipedia.org/wiki/Biblia
// https://hu.wikipedia.org/wiki/Héber_Biblia
// https://hu.wikipedia.org/wiki/Újszövetség
// https://hu.wikipedia.org/wiki/A_Biblia_k%C3%B6nyvei
// http://www.adorans.hu/node/88
// http://www.abbrevia.hu/index.php?menu=keresok&sub=5
// http://lexikon.katolikus.hu/ROVIDITESEK/BIBLIA.HTML
// http://biblia.blogger.hu/2011/09/30/3-a-biblia-felosztasa
// http://esti.mindenkilapja.hu/blog/19412368/renderpost/19478325/ujszovetseg
void TrStrings::initBooksHungarian()
{
  bookNameArr[0]  = QString("1 Mózes");                                 bookShortNameArr[0]  = QString("1 Mózes");                         bookMinNameArr[0]  = QString("1Móz");
  bookNameArr[1]  = QString("2 Mózes");                                 bookShortNameArr[1]  = QString("2 Mózes");                         bookMinNameArr[1]  = QString("2Móz");
  bookNameArr[2]  = QString("3 Mózes");                                 bookShortNameArr[2]  = QString("3 Mózes");                         bookMinNameArr[2]  = QString("3Móz");
  bookNameArr[3]  = QString("4 Mózes");                                 bookShortNameArr[3]  = QString("4 Mózes");                         bookMinNameArr[3]  = QString("4Móz");
  bookNameArr[4]  = QString("5 Mózes");                                 bookShortNameArr[4]  = QString("5 Mózes");                         bookMinNameArr[4]  = QString("5Móz");
  bookNameArr[5]  = QString("Józsué");                                  bookShortNameArr[5]  = QString("Józsué");                          bookMinNameArr[5]  = QString("Józs");
  bookNameArr[6]  = QString("Bírák");                                   bookShortNameArr[6]  = QString("Bírák");                           bookMinNameArr[6]  = QString("Bír");
  bookNameArr[7]  = QString("Ruth");                                    bookShortNameArr[7]  = QString("Ruth");                            bookMinNameArr[7]  = QString("Ruth");
  bookNameArr[8]  = QString("1 Sámuel");                                bookShortNameArr[8]  = QString("1 Sámuel");                        bookMinNameArr[8]  = QString("1Sám");
  bookNameArr[9]  = QString("2 Sámuel");                                bookShortNameArr[9]  = QString("2 Sámuel");                        bookMinNameArr[9]  = QString("2Sám");
  bookNameArr[10] = QString("1 Királyok");                              bookShortNameArr[10] = QString("1 Királyok");                      bookMinNameArr[10] = QString("1Kir");
  bookNameArr[11] = QString("2 Királyok");                              bookShortNameArr[11] = QString("2 Királyok");                      bookMinNameArr[11] = QString("2Kir");
  bookNameArr[12] = QString("1 Krónika");                               bookShortNameArr[12] = QString("1 Krónika");                       bookMinNameArr[12] = QString("1Krón");
  bookNameArr[13] = QString("2 Krónika");                               bookShortNameArr[13] = QString("2 Krónika");                       bookMinNameArr[13] = QString("2Krón");
  bookNameArr[14] = QString("Ezsdrás");                                 bookShortNameArr[14] = QString("Ezsdrás");                         bookMinNameArr[14] = QString("Ezdr");
  bookNameArr[15] = QString("Nehémiás");                                bookShortNameArr[15] = QString("Nehémiás");                        bookMinNameArr[15] = QString("Neh");
  bookNameArr[16] = QString("Eszter");                                  bookShortNameArr[16] = QString("Eszter");                          bookMinNameArr[16] = QString("Eszt");
  bookNameArr[17] = QString("Jób");                                     bookShortNameArr[17] = QString("Jób");                             bookMinNameArr[17] = QString("Jób");
  bookNameArr[18] = QString("Zsoltár");                                 bookShortNameArr[18] = QString("Zsoltár");                         bookMinNameArr[18] = QString("Zsolt");
  bookNameArr[19] = QString("Példabeszédek");                           bookShortNameArr[19] = QString("Példabeszédek");                   bookMinNameArr[19] = QString("Péld");
  bookNameArr[20] = QString("Prédikátor");                              bookShortNameArr[20] = QString("Prédikátor");                      bookMinNameArr[20] = QString("Préd");
  bookNameArr[21] = QString("Énekek éneke");                            bookShortNameArr[21] = QString("Énekek éneke");                    bookMinNameArr[21] = QString("Én");
  bookNameArr[22] = QString("Ézsaiás");                                 bookShortNameArr[22] = QString("Ézsaiás");                         bookMinNameArr[22] = QString("Éz");
  bookNameArr[23] = QString("Jeremiás");                                bookShortNameArr[23] = QString("Jeremiás");                        bookMinNameArr[23] = QString("Jer");
  bookNameArr[24] = QString("Jeremiás siralmai");                       bookShortNameArr[24] = QString("Jeremiás siralmai");               bookMinNameArr[24] = QString("Siral");
  bookNameArr[25] = QString("Ezékiel");                                 bookShortNameArr[25] = QString("Ezékiel");                         bookMinNameArr[25] = QString("Ez");
  bookNameArr[26] = QString("Dániel");                                  bookShortNameArr[26] = QString("Dániel");                          bookMinNameArr[26] = QString("Dán");
  bookNameArr[27] = QString("Hóseás");                                  bookShortNameArr[27] = QString("Hóseás");                          bookMinNameArr[27] = QString("Hós");
  bookNameArr[28] = QString("Jóel");                                    bookShortNameArr[28] = QString("Jóel");                            bookMinNameArr[28] = QString("Jóel");
  bookNameArr[29] = QString("Ámós") ;                                   bookShortNameArr[29] = QString("Ámós");                            bookMinNameArr[29] = QString("Ám");
  bookNameArr[30] = QString("Abdiás");                                  bookShortNameArr[30] = QString("Abdiás");                          bookMinNameArr[30] = QString("Abd");
  bookNameArr[31] = QString("Jónás");                                   bookShortNameArr[31] = QString("Jónás");                           bookMinNameArr[31] = QString("Jón");
  bookNameArr[32] = QString("Mikeás");                                  bookShortNameArr[32] = QString("Mikeás");                          bookMinNameArr[32] = QString("Mik");
  bookNameArr[33] = QString("Náhum");                                   bookShortNameArr[33] = QString("Náhum");                           bookMinNameArr[33] = QString("Náh");
  bookNameArr[34] = QString("Habakuk");                                 bookShortNameArr[34] = QString("Habakuk");                         bookMinNameArr[34] = QString("Hab");
  bookNameArr[35] = QString("Szofóniás");                               bookShortNameArr[35] = QString("Szofóniás");                       bookMinNameArr[35] = QString("Szof");
  bookNameArr[36] = QString("Aggeus");                                  bookShortNameArr[36] = QString("Aggeus");                          bookMinNameArr[36] = QString("Ag");
  bookNameArr[37] = QString("Zakariás");                                bookShortNameArr[37] = QString("Zakariás");                        bookMinNameArr[37] = QString("Zak");
  bookNameArr[38] = QString("Malakiás)");                               bookShortNameArr[38] = QString("Malakiás)");                       bookMinNameArr[38] = QString("Mal");

  bookNameArr[39] = QString("3 Ezsdrás");                               bookShortNameArr[39] = QString("3 Ezsdrás");                       bookMinNameArr[39] = QString("3Ezdr");
  bookNameArr[40] = QString("Tóbiás");                                  bookShortNameArr[40] = QString("Tóbiás");                          bookMinNameArr[40] = QString("Tób");
  bookNameArr[41] = QString("Judith");                                  bookShortNameArr[41] = QString("Judith");                          bookMinNameArr[41] = QString("Judith");
  bookNameArr[42] = QString("Bölcsesség");                              bookShortNameArr[42] = QString("Bölcsesség");                      bookMinNameArr[42] = QString("Bölcs");
  bookNameArr[43] = QString("Sirák fia");                               bookShortNameArr[43] = QString("Sirák fia");                       bookMinNameArr[43] = QString("Sir");
  bookNameArr[44] = QString("Jeremiás levele");                         bookShortNameArr[44] = QString("Jeremiás levele");                 bookMinNameArr[44] = QString("JerLev");
  bookNameArr[45] = QString("Báruk") ;                                  bookShortNameArr[45] = QString("Báruk");                           bookMinNameArr[45] = QString("Báruk");
  bookNameArr[46] = QString("1 Makkabeusok");                           bookShortNameArr[46] = QString("1 Makkabeusok");                   bookMinNameArr[46] = QString("1Mak");
  bookNameArr[47] = QString("2 Makkabeusok");                           bookShortNameArr[47] = QString("2 Makkabeusok");                   bookMinNameArr[47] = QString("2Mak");
  bookNameArr[48] = QString("3,4 Makkabeusok");                         bookShortNameArr[48] = QString("3,4 Makkabeusok");                 bookMinNameArr[48] = QString("3,4Mak");
  bookNameArr[49] = QString("4 Ezsdrás");                               bookShortNameArr[49] = QString("4 Ezsdrás");                       bookMinNameArr[49] = QString("4Ezdr");

  bookNameArr[50] = QString("Máté evangéliuma");                        bookShortNameArr[50] = QString("Máté");                            bookMinNameArr[50] = QString("Mt");
  bookNameArr[51] = QString("Márk evangéliuma");                        bookShortNameArr[51] = QString("Márk");                            bookMinNameArr[51] = QString("Mk");
  bookNameArr[52] = QString("Lukács evangéliuma");                      bookShortNameArr[52] = QString("Lukács");                          bookMinNameArr[52] = QString("Lk");
  bookNameArr[53] = QString("János evangéliuma");                       bookShortNameArr[53] = QString("János");                           bookMinNameArr[53] = QString("Jn");
  bookNameArr[54] = QString("Apostolok cselekedetei");                  bookShortNameArr[54] = QString("Cselekedetei");                    bookMinNameArr[54] = QString("Csel");

  bookNameArr[55] = QString("Pál levele a rómaiakhoz");                 bookShortNameArr[55] = QString("Róma");                            bookMinNameArr[55] = QString("Róm");
  bookNameArr[56] = QString("Pál első levele a Korintusiakhoz");        bookShortNameArr[56] = QString("1 Korinthus");                     bookMinNameArr[56] = QString("1Kor");
  bookNameArr[57] = QString("Pál második levele a Korintusiakhoz");     bookShortNameArr[57] = QString("2 Korinthus");                     bookMinNameArr[57] = QString("2Kor");
  bookNameArr[58] = QString("Pál levele a Galatákhoz");                 bookShortNameArr[58] = QString("Galata");                          bookMinNameArr[58] = QString("Gal");
  bookNameArr[59] = QString("Pál levele az Efézusiakhoz");              bookShortNameArr[59] = QString("Efezus");                          bookMinNameArr[59] = QString("Ef");
  bookNameArr[60] = QString("Pál levele a Filippibeliekhez");           bookShortNameArr[60] = QString("Filippi");                         bookMinNameArr[60] = QString("Fil");
  bookNameArr[61] = QString("Pál levele a Kolossébeliekhez");           bookShortNameArr[61] = QString("Kolossé");                         bookMinNameArr[61] = QString("Kol");
  bookNameArr[62] = QString("Pál első levele a Thesszalonikaiakhoz");   bookShortNameArr[62] = QString("1 Thesszalonika");                 bookMinNameArr[62] = QString("1Tesz");
  bookNameArr[63] = QString("Pál második levele a Thesszalonikaiakhoz");bookShortNameArr[63] = QString("2 Thesszalonika");                 bookMinNameArr[63] = QString("2Tesz");
  bookNameArr[64] = QString("Pál első levele Timóteushoz");             bookShortNameArr[64] = QString("1 Timóteus");                      bookMinNameArr[64] = QString("1Tim");
  bookNameArr[65] = QString("Pál második levele Timóteushoz");          bookShortNameArr[65] = QString("2 Timóteus");                      bookMinNameArr[65] = QString("2Tim");
  bookNameArr[66] = QString("Pál levele Tituszhoz");                    bookShortNameArr[66] = QString("Titusz");                          bookMinNameArr[66] = QString("Tit");
  bookNameArr[67] = QString("Pál levele Filemonhoz");                   bookShortNameArr[67] = QString("Filemon");                         bookMinNameArr[67] = QString("Filem");
  bookNameArr[68] = QString("A zsidókhoz írt levél");                   bookShortNameArr[68] = QString("Zsidók");                          bookMinNameArr[68] = QString("Zsid");

  bookNameArr[69] = QString("Jakab levele");                            bookShortNameArr[69] = QString("Jakab");                           bookMinNameArr[69] = QString("Jak");
  bookNameArr[70] = QString("Péter első levele");                       bookShortNameArr[70] = QString("1 Péter");                         bookMinNameArr[70] = QString("1Pét");
  bookNameArr[71] = QString("Péter második levele");                    bookShortNameArr[71] = QString("2 Péter");                         bookMinNameArr[71] = QString("2Pét");
  bookNameArr[72] = QString("János első levele");                       bookShortNameArr[72] = QString("1 János");                         bookMinNameArr[72] = QString("1Ján");
  bookNameArr[73] = QString("János második levele");                    bookShortNameArr[73] = QString("2 János");                         bookMinNameArr[73] = QString("2Ján");
  bookNameArr[74] = QString("János harmadik levele");                   bookShortNameArr[74] = QString("3 János");                         bookMinNameArr[74] = QString("3Ján");
  bookNameArr[75] = QString("Júdás levele");                            bookShortNameArr[75] = QString("Júdás");                           bookMinNameArr[75] = QString("Jud");

  bookNameArr[76] = QString("János jelenései");                         bookShortNameArr[76] = QString("Jelenések");                       bookMinNameArr[76] = QString("Jel");
}

// https://it.wikipedia.org/wiki/Bibbia
// https://it.wikipedia.org/wiki/Antico_Testamento
// https://it.wikipedia.org/wiki/Nuovo_Testamento
// https://it.wikipedia.org/wiki/Apocrifo
// http://www.laparola.net/abbrev.php
void TrStrings::initBooksItalian()
{
  bookNameArr[0]  = QString("Genesi");                                  bookShortNameArr[0]  = QString("Genesi");                          bookMinNameArr[0]  = QString("Genesi");//Gen
  bookNameArr[1]  = QString("Esodo");                                   bookShortNameArr[1]  = QString("Esodo");                           bookMinNameArr[1]  = QString("Esodo");//Eso
  bookNameArr[2]  = QString("Levitico");                                bookShortNameArr[2]  = QString("Levitico");                        bookMinNameArr[2]  = QString("Lev");//Le
  bookNameArr[3]  = QString("Numeri");                                  bookShortNameArr[3]  = QString("Numeri");                          bookMinNameArr[3]  = QString("Numeri");//Nu
  bookNameArr[4]  = QString("Deuteronomio");                            bookShortNameArr[4]  = QString("Deuteronomio");                    bookMinNameArr[4]  = QString("Deut");//De
  bookNameArr[5]  = QString("Giosuè");                                  bookShortNameArr[5]  = QString("Giosuè");                          bookMinNameArr[5]  = QString("Giosuè");//Gios
  bookNameArr[6]  = QString("Giudici");                                 bookShortNameArr[6]  = QString("Giudici");                         bookMinNameArr[6]  = QString("Giudici");//Giudic
  bookNameArr[7]  = QString("Rut");                                     bookShortNameArr[7]  = QString("Rut");                             bookMinNameArr[7]  = QString("Rut");//Rut
  bookNameArr[8]  = QString("1 Samuele");                               bookShortNameArr[8]  = QString("1 Samuele");                       bookMinNameArr[8]  = QString("1Sam");//1Sam
  bookNameArr[9]  = QString("2 Samuele");                               bookShortNameArr[9]  = QString("2 Samuele");                       bookMinNameArr[9]  = QString("2Sam");//2Sam
  bookNameArr[10] = QString("1 Re");                                    bookShortNameArr[10] = QString("1 Re");                            bookMinNameArr[10] = QString("1Re");//1Re
  bookNameArr[11] = QString("2 Re");                                    bookShortNameArr[11] = QString("2 Re");                            bookMinNameArr[11] = QString("2Re");//2Re
  bookNameArr[12] = QString("1 Cronache");                              bookShortNameArr[12] = QString("1 Cronache");                      bookMinNameArr[12] = QString("1Cron");//1Cr
  bookNameArr[13] = QString("2 Cronache");                              bookShortNameArr[13] = QString("2 Cronache");                      bookMinNameArr[13] = QString("2Cron");//2Cr
  bookNameArr[14] = QString("Esdra");                                   bookShortNameArr[14] = QString("Esdra");                           bookMinNameArr[14] = QString("Esdra");//Esd
  bookNameArr[15] = QString("Neemia");                                  bookShortNameArr[15] = QString("Neemia");                          bookMinNameArr[15] = QString("Neemia");//Ne
  bookNameArr[16] = QString("Ester");                                   bookShortNameArr[16] = QString("Ester");                           bookMinNameArr[16] = QString("Ester");//Est
  bookNameArr[17] = QString("Giobbe");                                  bookShortNameArr[17] = QString("Giobbe");                          bookMinNameArr[17] = QString("Giobbe");//Giob
  bookNameArr[18] = QString("Salmi");                                   bookShortNameArr[18] = QString("Salmi");                           bookMinNameArr[18] = QString("Salmi");//Sal
  bookNameArr[19] = QString("Proverbi");                                bookShortNameArr[19] = QString("Proverbi");                        bookMinNameArr[19] = QString("Prov");//Prov
  bookNameArr[20] = QString("Ecclesiaste");                             bookShortNameArr[20] = QString("Ecclesiaste");                     bookMinNameArr[20] = QString("Ecc");//Ec
  bookNameArr[21] = QString("Cantico dei Cantici");                     bookShortNameArr[21] = QString("Cantico");                         bookMinNameArr[21] = QString("CC");//CC
  bookNameArr[22] = QString("Isaia");                                   bookShortNameArr[22] = QString("Isaia");                           bookMinNameArr[22] = QString("Isaia");//Is
  bookNameArr[23] = QString("Geremia");                                 bookShortNameArr[23] = QString("Geremia");                         bookMinNameArr[23] = QString("Gerem");//Ger
  bookNameArr[24] = QString("Lamentazioni");                            bookShortNameArr[24] = QString("Lamentazioni");                    bookMinNameArr[24] = QString("Lamen");//Lam
  bookNameArr[25] = QString("Ezechiele");                               bookShortNameArr[25] = QString("Ezechiele");                       bookMinNameArr[25] = QString("Ezec");//Ez
  bookNameArr[26] = QString("Daniele");                                 bookShortNameArr[26] = QString("Daniele");                         bookMinNameArr[26] = QString("Dan");//Da
  bookNameArr[27] = QString("Osea");                                    bookShortNameArr[27] = QString("Osea");                            bookMinNameArr[27] = QString("Osea");//Os
  bookNameArr[28] = QString("Gioele");                                  bookShortNameArr[28] = QString("Gioele");                          bookMinNameArr[28] = QString("Gioele");//Gioe
  bookNameArr[29] = QString("Amos");                                    bookShortNameArr[29] = QString("Amos");                            bookMinNameArr[29] = QString("Amos");//Am
  bookNameArr[30] = QString("Abdia");                                   bookShortNameArr[30] = QString("Abdia");                           bookMinNameArr[30] = QString("Abdia");//Abd
  bookNameArr[31] = QString("Giona");                                   bookShortNameArr[31] = QString("Giona");                           bookMinNameArr[31] = QString("Giona");//Gion
  bookNameArr[32] = QString("Michea");                                  bookShortNameArr[32] = QString("Michea");                          bookMinNameArr[32] = QString("Michea");//Mi
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nahum");//Na
  bookNameArr[34] = QString("Abacuc");                                  bookShortNameArr[34] = QString("Abacuc");                          bookMinNameArr[34] = QString("Abacuc");//Abac
  bookNameArr[35] = QString("Sofonia");                                 bookShortNameArr[35] = QString("Sofonia");                         bookMinNameArr[35] = QString("Sof");//So
  bookNameArr[36] = QString("Aggeo");                                   bookShortNameArr[36] = QString("Aggeo");                           bookMinNameArr[36] = QString("Aggeo");//Ag
  bookNameArr[37] = QString("Zaccaria");                                bookShortNameArr[37] = QString("Zaccaria");                        bookMinNameArr[37] = QString("Zac");//Zac
  bookNameArr[38] = QString("Malachia");                                bookShortNameArr[38] = QString("Malachia");                        bookMinNameArr[38] = QString("Mal");//Mal

  bookNameArr[39] = QString("3 Esdra");                                 bookShortNameArr[39] = QString("3 Esdra");                         bookMinNameArr[39] = QString("3Esdra");//3Esd
  bookNameArr[40] = QString("Tobia");                                   bookShortNameArr[40] = QString("Tobia");                           bookMinNameArr[40] = QString("Tobia");//Tob
  bookNameArr[41] = QString("Giuditta");                                bookShortNameArr[41] = QString("Giuditta");                        bookMinNameArr[41] = QString("Giudit");//Giudit
  bookNameArr[42] = QString("Sapienza di Salomone");                    bookShortNameArr[42] = QString("Sapienza");                        bookMinNameArr[42] = QString("Sap");//Sap
  bookNameArr[43] = QString("Sapienza di Sirach");                      bookShortNameArr[43] = QString("Siracide"); /*Ecclesiastico*/      bookMinNameArr[43] = QString("Sir");//Sir /*Eccl*/
  bookNameArr[44] = QString("Lettera di Geremia");                      bookShortNameArr[44] = QString("Lettera di Geremia");              bookMinNameArr[44] = QString("LetGer");//LetGer
  bookNameArr[45] = QString("Baruc");                                   bookShortNameArr[45] = QString("Baruc");                           bookMinNameArr[45] = QString("Baruc");//Bar
  bookNameArr[46] = QString("1 Maccabei");                              bookShortNameArr[46] = QString("1 Maccabei");                      bookMinNameArr[46] = QString("1Macc");//1Macc
  bookNameArr[47] = QString("2 Maccabei");                              bookShortNameArr[47] = QString("2 Maccabei");                      bookMinNameArr[47] = QString("2Macc");//2Macc
  bookNameArr[48] = QString("3,4 Maccabei");                            bookShortNameArr[48] = QString("3,4 Maccabei");                    bookMinNameArr[48] = QString("3,4Macc");//3,4Macc
  bookNameArr[49] = QString("4 Esdra");                                 bookShortNameArr[49] = QString("4 Esdra");                         bookMinNameArr[49] = QString("4Esdra");//4Esd

  bookNameArr[50] = QString("Vangelo secondo Matteo");                  bookShortNameArr[50] = QString("Matteo");                          bookMinNameArr[50] = QString("Matteo");//Mat
  bookNameArr[51] = QString("Vangelo secondo Marco");                   bookShortNameArr[51] = QString("Marco");                           bookMinNameArr[51] = QString("Marco");//Mar
  bookNameArr[52] = QString("Vangelo secondo Luca");                    bookShortNameArr[52] = QString("Luca");                            bookMinNameArr[52] = QString("Luca");//Lu
  bookNameArr[53] = QString("Vangelo secondo Giovanni");                bookShortNameArr[53] = QString("Giovanni");                        bookMinNameArr[53] = QString("Giov");//Giov
  bookNameArr[54] = QString("Atti degli Apostoli");                     bookShortNameArr[54] = QString("Atti");                            bookMinNameArr[54] = QString("Atti");//At

  bookNameArr[55] = QString("Lettera ai Romani");                       bookShortNameArr[55] = QString("Romani");                          bookMinNameArr[55] = QString("Romani");//Ro
  bookNameArr[56] = QString("Prima lettera ai Corinzi");                bookShortNameArr[56] = QString("1 Corinzi");                       bookMinNameArr[56] = QString("1Cor");//1Co
  bookNameArr[57] = QString("Seconda lettera ai Corinzi");              bookShortNameArr[57] = QString("2 Corinzi");                       bookMinNameArr[57] = QString("2Cor");//2Co
  bookNameArr[58] = QString("Lettera ai Galati");                       bookShortNameArr[58] = QString("Galati");                          bookMinNameArr[58] = QString("Galati");//Ga
  bookNameArr[59] = QString("Lettera agli Efesini");                    bookShortNameArr[59] = QString("Efesini");                         bookMinNameArr[59] = QString("Efes");//Ef
  bookNameArr[60] = QString("Lettera ai Filippesi");                    bookShortNameArr[60] = QString("Filippesi");                       bookMinNameArr[60] = QString("Filip");//Fili
  bookNameArr[61] = QString("Lettera ai Colossesi");                    bookShortNameArr[61] = QString("Colossesi");                       bookMinNameArr[61] = QString("Colos");//Col
  bookNameArr[62] = QString("Prima lettera ai Tessalonicesi");          bookShortNameArr[62] = QString("1 Tessalonicesi");                 bookMinNameArr[62] = QString("1Tess");//1Te
  bookNameArr[63] = QString("Seconda lettera ai Tessalonicesi");        bookShortNameArr[63] = QString("2 Tessalonicesi");                 bookMinNameArr[63] = QString("2Tess");//2Te
  bookNameArr[64] = QString("Prima lettera a Timoteo");                 bookShortNameArr[64] = QString("1 Timoteo");                       bookMinNameArr[64] = QString("1Tim");//1Ti
  bookNameArr[65] = QString("Seconda lettera a Timoteo");               bookShortNameArr[65] = QString("2 Timoteo");                       bookMinNameArr[65] = QString("2Tim");//2Ti
  bookNameArr[66] = QString("Lettera a Tito");                          bookShortNameArr[66] = QString("Tito");                            bookMinNameArr[66] = QString("Tito");//Tit
  bookNameArr[67] = QString("Lettera a Filemone");                      bookShortNameArr[67] = QString("Filemone");                        bookMinNameArr[67] = QString("Filem");//File
  bookNameArr[68] = QString("Lettera agli Ebrei");                      bookShortNameArr[68] = QString("Ebrei");                           bookMinNameArr[68] = QString("Ebrei");//Eb

  bookNameArr[69] = QString("Lettera di Giacomo");                      bookShortNameArr[69] = QString("Giacomo");                         bookMinNameArr[69] = QString("Giac");//Giac
  bookNameArr[70] = QString("Prima lettera di Pietro");                 bookShortNameArr[70] = QString("1 Pietro");                        bookMinNameArr[70] = QString("1Piet");//1P
  bookNameArr[71] = QString("Seconda lettera di Pietro");               bookShortNameArr[71] = QString("2 Pietro");                        bookMinNameArr[71] = QString("2Piet");//2P
  bookNameArr[72] = QString("Prima lettera di Giovanni");               bookShortNameArr[72] = QString("1 Giovanni");                      bookMinNameArr[72] = QString("1Giov");//1G
  bookNameArr[73] = QString("Seconda lettera di Giovanni");             bookShortNameArr[73] = QString("2 Giovanni");                      bookMinNameArr[73] = QString("2Giov");//2G
  bookNameArr[74] = QString("Terza lettera di Giovanni");               bookShortNameArr[74] = QString("3 Giovanni");                      bookMinNameArr[74] = QString("3Giov");//3G
  bookNameArr[75] = QString("Lettera di Giuda");                        bookShortNameArr[75] = QString("Giuda");                           bookMinNameArr[75] = QString("Giuda");//Giuda

  bookNameArr[76] = QString("Apocalisse di Giovanni");                  bookShortNameArr[76] = QString("Apocalisse");                      bookMinNameArr[76] = QString("Apoc");//Ap
}

// https://pl.wikipedia.org/wiki/Biblia
// https://pl.wikipedia.org/wiki/Stary_Testament
// https://pl.wikipedia.org/wiki/Nowy_Testament
// https://pl.wikipedia.org/wiki/Apokryf
void TrStrings::initBooksPolish()
{
  bookNameArr[0]  = QString("Rodzaju");                                 bookShortNameArr[0]  = QString("Rodzaju");                         bookMinNameArr[0]  = QString("Rodzaju");//Rdz
  bookNameArr[1]  = QString("Wyjścia");                                 bookShortNameArr[1]  = QString("Wyjścia");                         bookMinNameArr[1]  = QString("Wyjścia");//Wj
  bookNameArr[2]  = QString("Kapłańska");                               bookShortNameArr[2]  = QString("Kapłańska");                       bookMinNameArr[2]  = QString("Kapł");//Kpł
  bookNameArr[3]  = QString("Liczb");                                   bookShortNameArr[3]  = QString("Liczb");                           bookMinNameArr[3]  = QString("Liczb");//Lb
  bookNameArr[4]  = QString("Powtórzonego Prawa");                      bookShortNameArr[4]  = QString("Powtórzonego");                    bookMinNameArr[4]  = QString("Powt");//Pwt
  bookNameArr[5]  = QString("Jozuego");                                 bookShortNameArr[5]  = QString("Jozuego");                         bookMinNameArr[5]  = QString("Jozuego");//Joz
  bookNameArr[6]  = QString("Sędziów");                                 bookShortNameArr[6]  = QString("Sędziów");                         bookMinNameArr[6]  = QString("Sędziów");//Sdz
  bookNameArr[7]  = QString("Rut");                                     bookShortNameArr[7]  = QString("Rut");                             bookMinNameArr[7]  = QString("Rut");//Rt
  bookNameArr[8]  = QString("1 Samuela");                               bookShortNameArr[8]  = QString("1 Samuela");                       bookMinNameArr[8]  = QString("1Sam");//1Sm
  bookNameArr[9]  = QString("2 Samuela");                               bookShortNameArr[9]  = QString("2 Samuela");                       bookMinNameArr[9]  = QString("2Sam");//2Sm
  bookNameArr[10] = QString("1 Królewska");                             bookShortNameArr[10] = QString("1 Królewska");                     bookMinNameArr[10] = QString("1Król");//1Krl
  bookNameArr[11] = QString("2 Królewska");                             bookShortNameArr[11] = QString("2 Królewska");                     bookMinNameArr[11] = QString("2Król");//2Krl
  bookNameArr[12] = QString("1 Kronik");                                bookShortNameArr[12] = QString("1 Kronik");                        bookMinNameArr[12] = QString("1Kron");//1Krn
  bookNameArr[13] = QString("2 Kronik");                                bookShortNameArr[13] = QString("2 Kronik");                        bookMinNameArr[13] = QString("2Kron");//2Krn
  bookNameArr[14] = QString("Ezdrasza");                                bookShortNameArr[14] = QString("Ezdrasza");                        bookMinNameArr[14] = QString("Ezdr");//Ezd
  bookNameArr[15] = QString("Nehemiasza");                              bookShortNameArr[15] = QString("Nehemiasza");                      bookMinNameArr[15] = QString("Neh");//Ne
  bookNameArr[16] = QString("Estery");                                  bookShortNameArr[16] = QString("Estery");                          bookMinNameArr[16] = QString("Estery");//Est
  bookNameArr[17] = QString("Joba"); /*Hioba*/                          bookShortNameArr[17] = QString("Joba"); /*Hioba*/                  bookMinNameArr[17] = QString("Joba");//Job /*Hi*/
  bookNameArr[18] = QString("Psalmów");                                 bookShortNameArr[18] = QString("Psalmów");                         bookMinNameArr[18] = QString("Ps");//Ps
  bookNameArr[19] = QString("Przypowieści Salomona");                   bookShortNameArr[19] = QString("Przypowieści");                    bookMinNameArr[19] = QString("Przyp");//Prz
  bookNameArr[20] = QString("Koheleta"); /*Eklezjastesa*/               bookShortNameArr[20] = QString("Koheleta)");                       bookMinNameArr[20] = QString("Koh");//Koh /*Ekl*/
  bookNameArr[21] = QString("Pieśń nad pieśniami");                     bookShortNameArr[21] = QString("Pieśń nad pieśniami");             bookMinNameArr[21] = QString("PnP");//PnP
  bookNameArr[22] = QString("Izajasza");                                bookShortNameArr[22] = QString("Izajasza");                        bookMinNameArr[22] = QString("Iz");//Iz
  bookNameArr[23] = QString("Jeremiasza");                              bookShortNameArr[23] = QString("Jeremiasza");                      bookMinNameArr[23] = QString("Jer");//Jr
  bookNameArr[24] = QString("Treny Jeremiasza"); /*Lamentacje Jeremiasza*/ bookShortNameArr[24] = QString("Treny Jeremiasza");             bookMinNameArr[24] = QString("Treny");// /*Lm*/
  bookNameArr[25] = QString("Ezechiela");                               bookShortNameArr[25] = QString("Ezechiela");                       bookMinNameArr[25] = QString("Ez");//Ez
  bookNameArr[26] = QString("Daniela");                                 bookShortNameArr[26] = QString("Daniela");                         bookMinNameArr[26] = QString("Dan");//Dn
  bookNameArr[27] = QString("Ozeasza");                                 bookShortNameArr[27] = QString("Ozeasza");                         bookMinNameArr[27] = QString("Oz");//Oz
  bookNameArr[28] = QString("Joela");                                   bookShortNameArr[28] = QString("Joela");                           bookMinNameArr[28] = QString("Joel");//Jl
  bookNameArr[29] = QString("Amosa");                                   bookShortNameArr[29] = QString("Amosa");                           bookMinNameArr[29] = QString("Am");//Am
  bookNameArr[30] = QString("Abdiasza");                                bookShortNameArr[30] = QString("Abdiasza");                        bookMinNameArr[30] = QString("Abd");//Ab
  bookNameArr[31] = QString("Jonasza");                                 bookShortNameArr[31] = QString("Jonasza");                         bookMinNameArr[31] = QString("Jon");//Jon
  bookNameArr[32] = QString("Micheasza");                               bookShortNameArr[32] = QString("Micheasza");                       bookMinNameArr[32] = QString("Mich");//Mi
  bookNameArr[33] = QString("Nahuma");                                  bookShortNameArr[33] = QString("Nahuma");                          bookMinNameArr[33] = QString("Nah");//Na
  bookNameArr[34] = QString("Habakuka");                                bookShortNameArr[34] = QString("Habakuka");                        bookMinNameArr[34] = QString("Hab");//Ha
  bookNameArr[35] = QString("Sofoniasza");                              bookShortNameArr[35] = QString("Sofoniasza");                      bookMinNameArr[35] = QString("Sof");//So
  bookNameArr[36] = QString("Aggeusza");                                bookShortNameArr[36] = QString("Aggeusza");                        bookMinNameArr[36] = QString("Ag");//Ag
  bookNameArr[37] = QString("Zachariasza");                             bookShortNameArr[37] = QString("Zachariasza");                     bookMinNameArr[37] = QString("Zach");//Za
  bookNameArr[38] = QString("Malachiasza)");                            bookShortNameArr[38] = QString("Malachiasza)");                    bookMinNameArr[38] = QString("Mal");//Ml

  bookNameArr[39] = QString("2 Ezdrasza");                              bookShortNameArr[39] = QString("3 Ezdrasza");                      bookMinNameArr[39] = QString("3Ezdr");//3Ezd
  bookNameArr[40] = QString("Tobiasza"); /*Tobita*/                     bookShortNameArr[40] = QString("Tobiasza"); /*Tobita*/             bookMinNameArr[40] = QString("Tob");//Tb /*Tob*/
  bookNameArr[41] = QString("Judyty");                                  bookShortNameArr[41] = QString("Judyty");                          bookMinNameArr[41] = QString("Judyty");//Jd
  bookNameArr[42] = QString("Mądrość Salomona");                        bookShortNameArr[42] = QString("Mądrość Salomona");                bookMinNameArr[42] = QString("Mądrość");//Mdr
  bookNameArr[43] = QString("Mądrość Syracha");                         bookShortNameArr[43] = QString("Mądrość Syracha"); /*Eklezjastyka*/bookMinNameArr[43] = QString("Syracha");//Syr /*Ekli*/
  bookNameArr[44] = QString("List Jeremiasza");                         bookShortNameArr[44] = QString("List Jeremiasza");                 bookMinNameArr[44] = QString("LJer");//LJr
  bookNameArr[45] = QString("Barucha") ;                                bookShortNameArr[45] = QString("Barucha");                         bookMinNameArr[45] = QString("Bar");//Ba
  bookNameArr[46] = QString("1 Machabejska");                           bookShortNameArr[46] = QString("1 Machabejska");                   bookMinNameArr[46] = QString("1Mach");//1Mch
  bookNameArr[47] = QString("2 Machabejska");                           bookShortNameArr[47] = QString("2 Machabejska");                   bookMinNameArr[47] = QString("2Mach");//2Mch
  bookNameArr[48] = QString("3,4 Machabejska");                         bookShortNameArr[48] = QString("3,4 Machabejska");                 bookMinNameArr[48] = QString("3,4Mach");//3,4Mch
  bookNameArr[49] = QString("3 Ezdrasza");                              bookShortNameArr[49] = QString("4 Ezdrasza");                      bookMinNameArr[49] = QString("4Ezdr");//4Ezd

  bookNameArr[50] = QString("Ewangelia Mateusza");                      bookShortNameArr[50] = QString("Mateusza");                        bookMinNameArr[50] = QString("Mat");//Mat
  bookNameArr[51] = QString("Ewangelia Marka");                         bookShortNameArr[51] = QString("Marka");                           bookMinNameArr[51] = QString("Mar");//Mar
  bookNameArr[52] = QString("Ewangelia Łukasza");                       bookShortNameArr[52] = QString("Łukasza");                         bookMinNameArr[52] = QString("Łuk");//Łuk
  bookNameArr[53] = QString("Ewangelia Jana");                          bookShortNameArr[53] = QString("Jana");                            bookMinNameArr[53] = QString("Jan");//Jan
  bookNameArr[54] = QString("Dzieje Apostolskie");                      bookShortNameArr[54] = QString("Dzieje");                          bookMinNameArr[54] = QString("D.A.");//Dz  Dz.Ap.

  bookNameArr[55] = QString("List do Rzymian");                         bookShortNameArr[55] = QString("Rzymian");                         bookMinNameArr[55] = QString("Rzym");//Rzym
  bookNameArr[56] = QString("1 List do Koryntian");                     bookShortNameArr[56] = QString("1 Koryntian");                     bookMinNameArr[56] = QString("1Kor");//1Kor
  bookNameArr[57] = QString("2 List do Koryntian");                     bookShortNameArr[57] = QString("2 Koryntian");                     bookMinNameArr[57] = QString("2Kor");//2Kor
  bookNameArr[58] = QString("List do Galatów");                         bookShortNameArr[58] = QString("Galatów");                         bookMinNameArr[58] = QString("Gal");//Gal
  bookNameArr[59] = QString("List do Efezjan");                         bookShortNameArr[59] = QString("Efezjan");                         bookMinNameArr[59] = QString("Efez");//Efez
  bookNameArr[60] = QString("List do Filipian");                        bookShortNameArr[60] = QString("Filipian");                        bookMinNameArr[60] = QString("Filip");//Filip
  bookNameArr[61] = QString("List do Kolosan");                         bookShortNameArr[61] = QString("Kolosan");                         bookMinNameArr[61] = QString("Kol");//Kol
  bookNameArr[62] = QString("1 List do Tesaloniczan");                  bookShortNameArr[62] = QString("1 Tesaloniczan");                  bookMinNameArr[62] = QString("1Tes");//1Tes
  bookNameArr[63] = QString("2 List do Tesaloniczan");                  bookShortNameArr[63] = QString("2 Tesaloniczan");                  bookMinNameArr[63] = QString("2Tes");//2Tes
  bookNameArr[64] = QString("1 List do Tymoteusza");                    bookShortNameArr[64] = QString("1 Tymoteusza");                    bookMinNameArr[64] = QString("1Tym");//1Tym
  bookNameArr[65] = QString("2 List do Tymoteusza");                    bookShortNameArr[65] = QString("2 Tymoteusza");                    bookMinNameArr[65] = QString("2Tym");//2Tym
  bookNameArr[66] = QString("List do Tytusa");                          bookShortNameArr[66] = QString("Tytusa");                          bookMinNameArr[66] = QString("Tyt");//Tyt
  bookNameArr[67] = QString("List do Filemona");                        bookShortNameArr[67] = QString("Filemona");                        bookMinNameArr[67] = QString("Filem");//Filem
  bookNameArr[68] = QString("List do Hebrajczyków");                    bookShortNameArr[68] = QString("Hebrajczyków");                    bookMinNameArr[68] = QString("Hebr");//Hebr

  bookNameArr[69] = QString("List Jakuba");                             bookShortNameArr[69] = QString("Jakuba");                          bookMinNameArr[69] = QString("Jak");//Jak
  bookNameArr[70] = QString("1 List Piotra");                           bookShortNameArr[70] = QString("1 Piotra");                        bookMinNameArr[70] = QString("1Piotr");//1Piotr
  bookNameArr[71] = QString("2 List Piotra");                           bookShortNameArr[71] = QString("2 Piotra");                        bookMinNameArr[71] = QString("2Piotr");//2Piotr
  bookNameArr[72] = QString("1 List Jana");                             bookShortNameArr[72] = QString("1 Jana");                          bookMinNameArr[72] = QString("1Jana");//1Jana
  bookNameArr[73] = QString("2 List Jana");                             bookShortNameArr[73] = QString("2 Jana");                          bookMinNameArr[73] = QString("2Jana");//2Jana
  bookNameArr[74] = QString("3 List Jana");                             bookShortNameArr[74] = QString("3 Jana");                          bookMinNameArr[74] = QString("3Jana");//3Jana
  bookNameArr[75] = QString("List Judy");                               bookShortNameArr[75] = QString("Judy");                            bookMinNameArr[75] = QString("Jud");//Jud

  bookNameArr[76] = QString("Apokalipsa Jana");                         bookShortNameArr[76] = QString("Apokalipsa");                      bookMinNameArr[76] = QString("Ap");//Ap
}

// https://ro.wikipedia.org/wiki/Biblia
// https://ro.wikipedia.org/wiki/Vechiul_Testament
// https://ro.wikipedia.org/wiki/Noul_Testament
// https://ro.wikipedia.org/wiki/Apocrif
// https://sites.google.com/site/bibliaarmateiromane/
void TrStrings::initBooksRomanian()
{
  bookNameArr[0]  = QString("Geneza"); /*Facerea*/                      bookShortNameArr[0]  = QString("Geneza");                          bookMinNameArr[0]  = QString("Geneza");//Gen
  bookNameArr[1]  = QString("Exod");                                    bookShortNameArr[1]  = QString("Exod");                            bookMinNameArr[1]  = QString("Exod");
  bookNameArr[2]  = QString("Levitic");                                 bookShortNameArr[2]  = QString("Levitic");                         bookMinNameArr[2]  = QString("Levit");//Lev
  bookNameArr[3]  = QString("Numeri");                                  bookShortNameArr[3]  = QString("Numeri");                          bookMinNameArr[3]  = QString("Numeri");//Num
  bookNameArr[4]  = QString("Deuteronom");                              bookShortNameArr[4]  = QString("Deuteronom");                      bookMinNameArr[4]  = QString("Deut");
  bookNameArr[5]  = QString("Iosua");                                   bookShortNameArr[5]  = QString("Iosua");                           bookMinNameArr[5]  = QString("Iosua");
  bookNameArr[6]  = QString("Judecători");                              bookShortNameArr[6]  = QString("Judecători");                      bookMinNameArr[6]  = QString("Judec");//Judc
  bookNameArr[7]  = QString("Rut");                                     bookShortNameArr[7]  = QString("Rut");                             bookMinNameArr[7]  = QString("Rut");
  bookNameArr[8]  = QString("1 Samuel");                                bookShortNameArr[8]  = QString("1 Samuel");                        bookMinNameArr[8]  = QString("1Sam");
  bookNameArr[9]  = QString("2 Samuel");                                bookShortNameArr[9]  = QString("2 Samuel");                        bookMinNameArr[9]  = QString("2Sam");
  bookNameArr[10] = QString("1 Regi");                                  bookShortNameArr[10] = QString("1 Regi");                          bookMinNameArr[10] = QString("1Regi");
  bookNameArr[11] = QString("2 Regi");                                  bookShortNameArr[11] = QString("2 Regi");                          bookMinNameArr[11] = QString("2Regi");
  bookNameArr[12] = QString("1 Cronici");                               bookShortNameArr[12] = QString("1 Cronici");                       bookMinNameArr[12] = QString("1Cron");
  bookNameArr[13] = QString("2 Cronici");                               bookShortNameArr[13] = QString("2 Cronici");                       bookMinNameArr[13] = QString("2Cron");
  bookNameArr[14] = QString("Ezra");                                    bookShortNameArr[14] = QString("Ezra");                            bookMinNameArr[14] = QString("Ezra");
  bookNameArr[15] = QString("Neemia");                                  bookShortNameArr[15] = QString("Neemia");                          bookMinNameArr[15] = QString("Neemia");//Neem
  bookNameArr[16] = QString("Estera");                                  bookShortNameArr[16] = QString("Estera");                          bookMinNameArr[16] = QString("Estera");//Est
  bookNameArr[17] = QString("Iov");                                     bookShortNameArr[17] = QString("Iov");                             bookMinNameArr[17] = QString("Iov");
  bookNameArr[18] = QString("Psalmi");                                  bookShortNameArr[18] = QString("Psalmi");                          bookMinNameArr[18] = QString("Ps");
  bookNameArr[19] = QString("Proverbe");                                bookShortNameArr[19] = QString("Proverbe");                        bookMinNameArr[19] = QString("Prov");
  bookNameArr[20] = QString("Ecleziast");                               bookShortNameArr[20] = QString("Ecleziast");                       bookMinNameArr[20] = QString("Ecl");
  bookNameArr[21] = QString("Cântarea Cântărilor");                     bookShortNameArr[21] = QString("Cântarea Cântărilor");             bookMinNameArr[21] = QString("Cânt");
  bookNameArr[22] = QString("Isaia");                                   bookShortNameArr[22] = QString("Isaia");                           bookMinNameArr[22] = QString("Isaia");//Isa
  bookNameArr[23] = QString("Ieremia");                                 bookShortNameArr[23] = QString("Ieremia");                         bookMinNameArr[23] = QString("Ier");
  bookNameArr[24] = QString("Plângerile lui Ieremia");                  bookShortNameArr[24] = QString("Plângerile lui Ieremia");          bookMinNameArr[24] = QString("PlIer");//Plang
  bookNameArr[25] = QString("Ezechiel");                                bookShortNameArr[25] = QString("Ezechiel");                        bookMinNameArr[25] = QString("Ezec");
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Daniel");//Dan
  bookNameArr[27] = QString("Osea");                                    bookShortNameArr[27] = QString("Osea");                            bookMinNameArr[27] = QString("Osea");
  bookNameArr[28] = QString("Ioel");                                    bookShortNameArr[28] = QString("Ioel");                            bookMinNameArr[28] = QString("Ioel");
  bookNameArr[29] = QString("Amos");                                    bookShortNameArr[29] = QString("Amos");                            bookMinNameArr[29] = QString("Amos");
  bookNameArr[30] = QString("Obadia");                                  bookShortNameArr[30] = QString("Obadia");                          bookMinNameArr[30] = QString("Obadia");//Obad
  bookNameArr[31] = QString("Iona");                                    bookShortNameArr[31] = QString("Iona");                            bookMinNameArr[31] = QString("Iona");
  bookNameArr[32] = QString("Mica");                                    bookShortNameArr[32] = QString("Mica");                            bookMinNameArr[32] = QString("Mica");
  bookNameArr[33] = QString("Naum");                                    bookShortNameArr[33] = QString("Naum");                            bookMinNameArr[33] = QString("Naum");
  bookNameArr[34] = QString("Habacuc");                                 bookShortNameArr[34] = QString("Habacuc");                         bookMinNameArr[34] = QString("Hab");
  bookNameArr[35] = QString("Țefania");                                 bookShortNameArr[35] = QString("Țefania");                         bookMinNameArr[35] = QString("Țef");
  bookNameArr[36] = QString("Hagai");                                   bookShortNameArr[36] = QString("Hagai");                           bookMinNameArr[36] = QString("Hagai");//Hag
  bookNameArr[37] = QString("Zaharia");                                 bookShortNameArr[37] = QString("Zaharia");                         bookMinNameArr[37] = QString("Zah");
  bookNameArr[38] = QString("Maleahi");                                 bookShortNameArr[38] = QString("Maleahi");                         bookMinNameArr[38] = QString("Mal");

  bookNameArr[39] = QString("3 Ezdra");                                 bookShortNameArr[39] = QString("3 Ezdra");                         bookMinNameArr[39] = QString("3Ezdra");
  bookNameArr[40] = QString("Tobit");                                   bookShortNameArr[40] = QString("Tobit");                           bookMinNameArr[40] = QString("Tobit");
  bookNameArr[41] = QString("Iudita");                                  bookShortNameArr[41] = QString("Iudita");                          bookMinNameArr[41] = QString("Iudita");
  bookNameArr[42] = QString("Înțelepciunea lui Solomon");               bookShortNameArr[42] = QString("Înțelepciunea");                   bookMinNameArr[42] = QString("ÎnțSol");
  bookNameArr[43] = QString("Înțelepciunea lui Sirah");                 bookShortNameArr[43] = QString("Sirah"); /*Ecleziastic*/           bookMinNameArr[43] = QString("Sirah");
  bookNameArr[44] = QString("Epistola lui Ieremia");                    bookShortNameArr[44] = QString("Epistola lui Ieremia");            bookMinNameArr[44] = QString("EpIer");
  bookNameArr[45] = QString("Baruh");                                   bookShortNameArr[45] = QString("Baruh");                           bookMinNameArr[45] = QString("Baruh");
  bookNameArr[46] = QString("1 Macabei");                               bookShortNameArr[46] = QString("1 Macabei");                       bookMinNameArr[46] = QString("1Mac");
  bookNameArr[47] = QString("2 Macabei");                               bookShortNameArr[47] = QString("2 Macabei");                       bookMinNameArr[47] = QString("2Mac");
  bookNameArr[48] = QString("3,4 Macabei");                             bookShortNameArr[48] = QString("3,4 Macabei");                     bookMinNameArr[48] = QString("3,4Mac");
  bookNameArr[49] = QString("4 Ezdra");                                 bookShortNameArr[49] = QString("4 Ezdra");                         bookMinNameArr[49] = QString("4Ezdra");

  bookNameArr[50] = QString("Evanghelia după Matei");                   bookShortNameArr[50] = QString("Matei");                           bookMinNameArr[50] = QString("Matei");//Mat
  bookNameArr[51] = QString("Evanghelia după Marcu");                   bookShortNameArr[51] = QString("Marcu");                           bookMinNameArr[51] = QString("Marcu");//Marc
  bookNameArr[52] = QString("Evanghelia după Luca");                    bookShortNameArr[52] = QString("Luca");                            bookMinNameArr[52] = QString("Luca");//Luc
  bookNameArr[53] = QString("Evanghelia după Ioan");                    bookShortNameArr[53] = QString("Ioan");                            bookMinNameArr[53] = QString("Ioan");//Ioan
  bookNameArr[54] = QString("Faptele Apostolilor");                     bookShortNameArr[54] = QString("Faptele");                         bookMinNameArr[54] = QString("Fapte");//Fapt

  bookNameArr[55] = QString("Epistola Romani");                         bookShortNameArr[55] = QString("Romani");                          bookMinNameArr[55] = QString("Romani");//Rom
  bookNameArr[56] = QString("Epistola 1 Corinteni");                    bookShortNameArr[56] = QString("1 Corinteni");                     bookMinNameArr[56] = QString("1Cor");//1Cor
  bookNameArr[57] = QString("Epistola 2 Corinteni");                    bookShortNameArr[57] = QString("2 Corinteni");                     bookMinNameArr[57] = QString("2Cor");//2Cor
  bookNameArr[58] = QString("Epistola Galateni");                       bookShortNameArr[58] = QString("Galateni");                        bookMinNameArr[58] = QString("Galat");//Gal
  bookNameArr[59] = QString("Epistola Efeseni");                        bookShortNameArr[59] = QString("Efeseni");                         bookMinNameArr[59] = QString("Efes");//Efes
  bookNameArr[60] = QString("Epistola Filipeni");                       bookShortNameArr[60] = QString("Filipeni");                        bookMinNameArr[60] = QString("Filip");//Filip
  bookNameArr[61] = QString("Epistola Coloseni");                       bookShortNameArr[61] = QString("Coloseni");                        bookMinNameArr[61] = QString("Colos");//Col
  bookNameArr[62] = QString("Epistola 1 Tesaloniceni");                 bookShortNameArr[62] = QString("1 Tesaloniceni");                  bookMinNameArr[62] = QString("1Tes");//1Tes
  bookNameArr[63] = QString("Epistola 2 Tesaloniceni");                 bookShortNameArr[63] = QString("2 Tesaloniceni");                  bookMinNameArr[63] = QString("2Tes");//2Tes
  bookNameArr[64] = QString("Epistola 1 Timotei");                      bookShortNameArr[64] = QString("1 Timotei");                       bookMinNameArr[64] = QString("1Tim");//1Tim
  bookNameArr[65] = QString("Epistola 2 Timotei");                      bookShortNameArr[65] = QString("2 Timotei");                       bookMinNameArr[65] = QString("2Tim");//2Tim
  bookNameArr[66] = QString("Epistola Titus");                          bookShortNameArr[66] = QString("Titus");                           bookMinNameArr[66] = QString("Titus");//Tit
  bookNameArr[67] = QString("Epistola Filimon");                        bookShortNameArr[67] = QString("Filimon");                         bookMinNameArr[67] = QString("Filim");//Filim
  bookNameArr[68] = QString("Epistola Evrei");                          bookShortNameArr[68] = QString("Evrei");                           bookMinNameArr[68] = QString("Evrei");//Evr

  bookNameArr[69] = QString("Epistola Iacov");                          bookShortNameArr[69] = QString("Iacov");                           bookMinNameArr[69] = QString("Iacov");//Iac
  bookNameArr[70] = QString("Epistola 1 Petru");                        bookShortNameArr[70] = QString("1 Petru");                         bookMinNameArr[70] = QString("1Petru");//1Pet
  bookNameArr[71] = QString("Epistola 2 Petru");                        bookShortNameArr[71] = QString("2 Petru");                         bookMinNameArr[71] = QString("2Petru");//2Pet
  bookNameArr[72] = QString("Epistola 1 Ioan");                         bookShortNameArr[72] = QString("1 Ioan");                          bookMinNameArr[72] = QString("1Ioan");//1Ioan
  bookNameArr[73] = QString("Epistola 2 Ioan");                         bookShortNameArr[73] = QString("2 Ioan");                          bookMinNameArr[73] = QString("2Ioan");//2Ioan
  bookNameArr[74] = QString("Epistola 3 Ioan");                         bookShortNameArr[74] = QString("3 Ioan");                          bookMinNameArr[74] = QString("3Ioan");//3Ioan
  bookNameArr[75] = QString("Epistola Iuda");                           bookShortNameArr[75] = QString("Iuda");                            bookMinNameArr[75] = QString("Iuda");//Iuda

  bookNameArr[76] = QString("Apocalipsa Ioan");                         bookShortNameArr[76] = QString("Apocalipsa"); /*Revelaţia*/        bookMinNameArr[76] = QString("Apoc");//Apoc
}

// https://ru.wikipedia.org/wiki/Библия
// https://ru.wikipedia.org/wiki/Книги_Библии
// https://ru.wikipedia.org/wiki/Сокращения_названий_книг_Библии
// https://ru.wikipedia.org/wiki/Библейский_канон
// https://upload.wikimedia.org/wikipedia/commons/2/23/OT_canon_png.png
void TrStrings::initBooksRussian()
{
  bookNameArr[0]  = QString("Бытие");                                   bookShortNameArr[0]  = QString("Бытие");                           bookMinNameArr[0]  = QString("Бытие");
  bookNameArr[1]  = QString("Исход");                                   bookShortNameArr[1]  = QString("Исход");                           bookMinNameArr[1]  = QString("Исход");
  bookNameArr[2]  = QString("Левит");                                   bookShortNameArr[2]  = QString("Левит");                           bookMinNameArr[2]  = QString("Левит");
  bookNameArr[3]  = QString("Числа");                                   bookShortNameArr[3]  = QString("Числа");                           bookMinNameArr[3]  = QString("Числа");
  bookNameArr[4]  = QString("Второзаконие");                            bookShortNameArr[4]  = QString("Второзаконие");                    bookMinNameArr[4]  = QString("Втор.");
  bookNameArr[5]  = QString("Иисус Навин");                             bookShortNameArr[5]  = QString("Иисус Навин");                     bookMinNameArr[5]  = QString("И.Н.");
  bookNameArr[6]  = QString("Судей Израилевых");                        bookShortNameArr[6]  = QString("Судей");                           bookMinNameArr[6]  = QString("Судей");
  bookNameArr[7]  = QString("Руфь");                                    bookShortNameArr[7]  = QString("Руфь");                            bookMinNameArr[7]  = QString("Руфь");
  bookNameArr[8]  = QString("1 Царств");                                bookShortNameArr[8]  = QString("1 Царств");                        bookMinNameArr[8]  = QString("1Цар.");
  bookNameArr[9]  = QString("2 Царств");                                bookShortNameArr[9]  = QString("2 Царств");                        bookMinNameArr[9]  = QString("2Цар.");
  bookNameArr[10] = QString("3 Царств");                                bookShortNameArr[10] = QString("3 Царств");                        bookMinNameArr[10] = QString("3Цар.");
  bookNameArr[11] = QString("4 Царств");                                bookShortNameArr[11] = QString("4 Царств");                        bookMinNameArr[11] = QString("4Цар.");
  bookNameArr[12] = QString("1 Паралипоменон");                         bookShortNameArr[12] = QString("1 Паралипоменон");                 bookMinNameArr[12] = QString("1Пар.");
  bookNameArr[13] = QString("2 Паралипоменон");                         bookShortNameArr[13] = QString("2 Паралипоменон");                 bookMinNameArr[13] = QString("2Пар.");
  bookNameArr[14] = QString("Ездра");                                   bookShortNameArr[14] = QString("Ездра");                           bookMinNameArr[14] = QString("Ездра");
  bookNameArr[15] = QString("Неемия");                                  bookShortNameArr[15] = QString("Неемия");                          bookMinNameArr[15] = QString("Неемия");
  bookNameArr[16] = QString("Есфирь");                                  bookShortNameArr[16] = QString("Есфирь");                          bookMinNameArr[16] = QString("Есфирь");
  bookNameArr[17] = QString("Иов");                                     bookShortNameArr[17] = QString("Иов");                             bookMinNameArr[17] = QString("Иов");
  bookNameArr[18] = QString("Псалмы");                                  bookShortNameArr[18] = QString("Псалмы");                          bookMinNameArr[18] = QString("Пс.");
  bookNameArr[19] = QString("Притчи Соломоновых");                      bookShortNameArr[19] = QString("Притчи");                          bookMinNameArr[19] = QString("Пр.");
  bookNameArr[20] = QString("Екклесиаст") ;                             bookShortNameArr[20] = QString("Екклесиаст") ;                     bookMinNameArr[20] = QString("Екк.");
  bookNameArr[21] = QString("Песнь Песней Соломона");                   bookShortNameArr[21] = QString("Песнь Песней");                    bookMinNameArr[21] = QString("П.П.");
  bookNameArr[22] = QString("Исайя");                                   bookShortNameArr[22] = QString("Исайя");                           bookMinNameArr[22] = QString("Исайя");
  bookNameArr[23] = QString("Иеремия");                                 bookShortNameArr[23] = QString("Иеремия");                         bookMinNameArr[23] = QString("Иер.");
  bookNameArr[24] = QString("Плач Иеремии");                            bookShortNameArr[24] = QString("Плач Иеремии");                    bookMinNameArr[24] = QString("Плач.");
  bookNameArr[25] = QString("Иезекиль");                                bookShortNameArr[25] = QString("Иезекиль");                        bookMinNameArr[25] = QString("Иезек.");
  bookNameArr[26] = QString("Даниил");                                  bookShortNameArr[26] = QString("Даниил");                          bookMinNameArr[26] = QString("Даниил");
  bookNameArr[27] = QString("Осия");                                    bookShortNameArr[27] = QString("Осия");                            bookMinNameArr[27] = QString("Осия");
  bookNameArr[28] = QString("Иоиль");                                   bookShortNameArr[28] = QString("Иоиль");                           bookMinNameArr[28] = QString("Иоиль");
  bookNameArr[29] = QString("Амос");                                    bookShortNameArr[29] = QString("Амос");                            bookMinNameArr[29] = QString("Амос");
  bookNameArr[30] = QString("Авдий");                                   bookShortNameArr[30] = QString("Авдий");                           bookMinNameArr[30] = QString("Авдий");
  bookNameArr[31] = QString("Йона");                                    bookShortNameArr[31] = QString("Йона");                            bookMinNameArr[31] = QString("Йона");
  bookNameArr[32] = QString("Михей");                                   bookShortNameArr[32] = QString("Михей");                           bookMinNameArr[32] = QString("Михей");
  bookNameArr[33] = QString("Наум");                                    bookShortNameArr[33] = QString("Наум");                            bookMinNameArr[33] = QString("Наум");
  bookNameArr[34] = QString("Авваккум");                                bookShortNameArr[34] = QString("Авваккум");                        bookMinNameArr[34] = QString("Авв.");
  bookNameArr[35] = QString("Софония");                                 bookShortNameArr[35] = QString("Софония");                         bookMinNameArr[35] = QString("Соф.");
  bookNameArr[36] = QString("Аггей");                                   bookShortNameArr[36] = QString("Аггей");                           bookMinNameArr[36] = QString("Аггей");
  bookNameArr[37] = QString("Захария");                                 bookShortNameArr[37] = QString("Захария");                         bookMinNameArr[37] = QString("Зах.");
  bookNameArr[38] = QString("Малахия)");                                bookShortNameArr[38] = QString("Малахия)");                        bookMinNameArr[38] = QString("Мал.");

  bookNameArr[39] = QString("2 Ездра");                                 bookShortNameArr[39] = QString("2 Ездра");                         bookMinNameArr[39] = QString("2Ездра");
  bookNameArr[40] = QString("Товит");                                   bookShortNameArr[40] = QString("Товит");                           bookMinNameArr[40] = QString("Товит");
  bookNameArr[41] = QString("Иудифь");                                  bookShortNameArr[41] = QString("Иудифь");                          bookMinNameArr[41] = QString("Иудифь");
  bookNameArr[42] = QString("Премудрость Соломона");                    bookShortNameArr[42] = QString("Премудрость Соломона");            bookMinNameArr[42] = QString("Пр.Сол.");
  bookNameArr[43] = QString("Премудрость Иисус, сына Сирах");           bookShortNameArr[43] = QString("Иисус Сирах");                     bookMinNameArr[43] = QString("Сирах");
  bookNameArr[44] = QString("Послание Иеремии");                        bookShortNameArr[44] = QString("Послание Иеремии");                bookMinNameArr[44] = QString("Пос.Иер.");
  bookNameArr[45] = QString("Варух") ;                                  bookShortNameArr[45] = QString("Варух");                           bookMinNameArr[45] = QString("Варух");
  bookNameArr[46] = QString("1 Маккавейская");                          bookShortNameArr[46] = QString("1 Маккавейская");                  bookMinNameArr[46] = QString("1Мак.");
  bookNameArr[47] = QString("2 Маккавейская");                          bookShortNameArr[47] = QString("2 Маккавейская");                  bookMinNameArr[47] = QString("2Мак.");
  bookNameArr[48] = QString("3,4 Маккавейская");                        bookShortNameArr[48] = QString("3,4 Маккавейская");                bookMinNameArr[48] = QString("3,4Мак.");
  bookNameArr[49] = QString("3 Ездра");                                 bookShortNameArr[49] = QString("3 Ездра");                         bookMinNameArr[49] = QString("3Ездра");

  bookNameArr[50] = QString("Евангелие от Матфея");                     bookShortNameArr[50] = QString("Матфея");                          bookMinNameArr[50] = QString("Матфея");
  bookNameArr[51] = QString("Евангелие от Марка");                      bookShortNameArr[51] = QString("Марка");                           bookMinNameArr[51] = QString("Марка");
  bookNameArr[52] = QString("Евангелие от Луки");                       bookShortNameArr[52] = QString("Луки");                            bookMinNameArr[52] = QString("Луки");
  bookNameArr[53] = QString("Евангелие от Иоанна");                     bookShortNameArr[53] = QString("Иоанна");                          bookMinNameArr[53] = QString("Иоанна");
  bookNameArr[54] = QString("Деяния Апостолов");                        bookShortNameArr[54] = QString("Деяния");                          bookMinNameArr[54] = QString("Д.А.");

  bookNameArr[55] = QString("Римлянам");                                bookShortNameArr[55] = QString("Римлянам");                        bookMinNameArr[55] = QString("Рим.");
  bookNameArr[56] = QString("1 Коринфянам");                            bookShortNameArr[56] = QString("1 Коринфянам");                    bookMinNameArr[56] = QString("1Кор.");
  bookNameArr[57] = QString("2 Коринфянам");                            bookShortNameArr[57] = QString("2 Коринфянам");                    bookMinNameArr[57] = QString("2Кор.");
  bookNameArr[58] = QString("Галатам");                                 bookShortNameArr[58] = QString("Галатам");                         bookMinNameArr[58] = QString("Гал.");
  bookNameArr[59] = QString("Ефесянам");                                bookShortNameArr[59] = QString("Ефесянам");                        bookMinNameArr[59] = QString("Ефес.");
  bookNameArr[60] = QString("Филиппийцам");                             bookShortNameArr[60] = QString("Филиппийцам");                     bookMinNameArr[60] = QString("Филип.");
  bookNameArr[61] = QString("Колоссянам");                              bookShortNameArr[61] = QString("Колоссянам");                      bookMinNameArr[61] = QString("Колос.");
  bookNameArr[62] = QString("1 Фессалоникийцам");                       bookShortNameArr[62] = QString("1 Фессалоникийцам");               bookMinNameArr[62] = QString("1Фес.");
  bookNameArr[63] = QString("2 Фессалоникийцам");                       bookShortNameArr[63] = QString("2 Фессалоникийцам");               bookMinNameArr[63] = QString("2Фес.");
  bookNameArr[64] = QString("1 Тимофею");                               bookShortNameArr[64] = QString("1 Тимофею");                       bookMinNameArr[64] = QString("1Тим.");
  bookNameArr[65] = QString("2 Тимофею");                               bookShortNameArr[65] = QString("2 Тимофею");                       bookMinNameArr[65] = QString("2Тим.");
  bookNameArr[66] = QString("Титу");                                    bookShortNameArr[66] = QString("Титу");                            bookMinNameArr[66] = QString("Титу");
  bookNameArr[67] = QString("Филимону");                                bookShortNameArr[67] = QString("Филимону");                        bookMinNameArr[67] = QString("Филим.");
  bookNameArr[68] = QString("Евреям");                                  bookShortNameArr[68] = QString("Евреям");                          bookMinNameArr[68] = QString("Евреям");

  bookNameArr[69] = QString("Иакова");                                  bookShortNameArr[69] = QString("Иакова");                          bookMinNameArr[69] = QString("Иакова");
  bookNameArr[70] = QString("1 Петра");                                 bookShortNameArr[70] = QString("1 Петра");                         bookMinNameArr[70] = QString("1Петра");
  bookNameArr[71] = QString("2 Петра");                                 bookShortNameArr[71] = QString("2 Петра");                         bookMinNameArr[71] = QString("2Петра");
  bookNameArr[72] = QString("1 Иоанна");                                bookShortNameArr[72] = QString("1 Иоанна");                        bookMinNameArr[72] = QString("1Иоан.");
  bookNameArr[73] = QString("2 Иоанна");                                bookShortNameArr[73] = QString("2 Иоанна");                        bookMinNameArr[73] = QString("2Иоан.");
  bookNameArr[74] = QString("3 Иоанна");                                bookShortNameArr[74] = QString("3 Иоанна");                        bookMinNameArr[74] = QString("3Иоан.");
  bookNameArr[75] = QString("Иуды");                                    bookShortNameArr[75] = QString("Иуды");                            bookMinNameArr[75] = QString("Иуды");

  bookNameArr[76] = QString("Откровение Иоанна");                       bookShortNameArr[76] = QString("Откровение");                      bookMinNameArr[76] = QString("Откр.");
}

// https://es.wikipedia.org/wiki/Biblia
// https://es.wikipedia.org/wiki/Libros_de_la_Biblia
// https://es.wikipedia.org/wiki/Antiguo_Testamento
// https://es.wikipedia.org/wiki/Nuevo_Testamento
// https://es.wikipedia.org/wiki/Apócrifo_(religión)
// http://www.biblija.net/help.es/abbrevs.es.php
void TrStrings::initBooksSpanish()
{
  bookNameArr[0]  = QString("Génesis");                                 bookShortNameArr[0]  = QString("Génesis");                         bookMinNameArr[0]  = QString("Gén");//Gn
  bookNameArr[1]  = QString("Éxodo");                                   bookShortNameArr[1]  = QString("Éxodo");                           bookMinNameArr[1]  = QString("Éxodo");//Ex
  bookNameArr[2]  = QString("Levítico");                                bookShortNameArr[2]  = QString("Levítico");                        bookMinNameArr[2]  = QString("Lev");//Lv
  bookNameArr[3]  = QString("Números");                                 bookShortNameArr[3]  = QString("Números");                         bookMinNameArr[3]  = QString("Núm");//Nm
  bookNameArr[4]  = QString("Deuteronomio");                            bookShortNameArr[4]  = QString("Deuteronomio");                    bookMinNameArr[4]  = QString("Deut");//Dt
  bookNameArr[5]  = QString("Josué");                                   bookShortNameArr[5]  = QString("Josué");                           bookMinNameArr[5]  = QString("Josué");//Jos
  bookNameArr[6]  = QString("Jueces");                                  bookShortNameArr[6]  = QString("Jueces");                          bookMinNameArr[6]  = QString("Jueces");//Jue
  bookNameArr[7]  = QString("Rut");                                     bookShortNameArr[7]  = QString("Rut");                             bookMinNameArr[7]  = QString("Rut");//Rut
  bookNameArr[8]  = QString("1 Samuel");                                bookShortNameArr[8]  = QString("1 Samuel");                        bookMinNameArr[8]  = QString("1Sam");//1S
  bookNameArr[9]  = QString("2 Samuel");                                bookShortNameArr[9]  = QString("2 Samuel");                        bookMinNameArr[9]  = QString("2Sam");//2S
  bookNameArr[10] = QString("1 Reyes");                                 bookShortNameArr[10] = QString("1 Reyes");                         bookMinNameArr[10] = QString("1Reyes");//1R
  bookNameArr[11] = QString("2 Reyes");                                 bookShortNameArr[11] = QString("2 Reyes");                         bookMinNameArr[11] = QString("2Reyes");//2R
  bookNameArr[12] = QString("1 Crónicas");                              bookShortNameArr[12] = QString("1 Crónicas");                      bookMinNameArr[12] = QString("1Crón");//1Cr
  bookNameArr[13] = QString("2 Crónicas");                              bookShortNameArr[13] = QString("2 Crónicas");                      bookMinNameArr[13] = QString("2Crón");//2Cr
  bookNameArr[14] = QString("Esdras");                                  bookShortNameArr[14] = QString("Esdras");                          bookMinNameArr[14] = QString("Esdras");//Esd
  bookNameArr[15] = QString("Nehemías");                                bookShortNameArr[15] = QString("Nehemías");                        bookMinNameArr[15] = QString("Nehem");//Neh
  bookNameArr[16] = QString("Ester");                                   bookShortNameArr[16] = QString("Ester");                           bookMinNameArr[16] = QString("Ester");//Est
  bookNameArr[17] = QString("Job");                                     bookShortNameArr[17] = QString("Job");                             bookMinNameArr[17] = QString("Job");//Job
  bookNameArr[18] = QString("Salmos");                                  bookShortNameArr[18] = QString("Salmos");                          bookMinNameArr[18] = QString("Sal");//Sal
  bookNameArr[19] = QString("Proverbios");                              bookShortNameArr[19] = QString("Proverbios");                      bookMinNameArr[19] = QString("Pr");//Pr
  bookNameArr[20] = QString("Eclesiastés");                             bookShortNameArr[20] = QString("Eclesiastés");                     bookMinNameArr[20] = QString("Ecles");//Ec
  bookNameArr[21] = QString("Cantar de los Cantares");                  bookShortNameArr[21] = QString("Cantares");                        bookMinNameArr[21] = QString("CC");//Cnt
  bookNameArr[22] = QString("Isaías");                                  bookShortNameArr[22] = QString("Isaías");                          bookMinNameArr[22] = QString("Isaías");//Is
  bookNameArr[23] = QString("Jeremías");                                bookShortNameArr[23] = QString("Jeremías");                        bookMinNameArr[23] = QString("Jerem");//Jer
  bookNameArr[24] = QString("Lamentaciones");                           bookShortNameArr[24] = QString("Lamentaciones");                   bookMinNameArr[24] = QString("Lamen");//Lm
  bookNameArr[25] = QString("Ezequiel");                                bookShortNameArr[25] = QString("Ezequiel");                        bookMinNameArr[25] = QString("Ezeq");//Ez
  bookNameArr[26] = QString("Daniel");                                  bookShortNameArr[26] = QString("Daniel");                          bookMinNameArr[26] = QString("Daniel");//Dn
  bookNameArr[27] = QString("Oseas");                                   bookShortNameArr[27] = QString("Oseas");                           bookMinNameArr[27] = QString("Oseas");//Os
  bookNameArr[28] = QString("Joel");                                    bookShortNameArr[28] = QString("Joel");                            bookMinNameArr[28] = QString("Joel");//Jl
  bookNameArr[29] = QString("Amós");                                    bookShortNameArr[29] = QString("Amós");                            bookMinNameArr[29] = QString("Amós");//Am
  bookNameArr[30] = QString("Abdías");                                  bookShortNameArr[30] = QString("Abdías");                          bookMinNameArr[30] = QString("Abdías");//Abd
  bookNameArr[31] = QString("Jonás");                                   bookShortNameArr[31] = QString("Jonás");                           bookMinNameArr[31] = QString("Jonás");//Jon
  bookNameArr[32] = QString("Miqueas");                                 bookShortNameArr[32] = QString("Miqueas");                         bookMinNameArr[32] = QString("Miq");//Miq
  bookNameArr[33] = QString("Nahum");                                   bookShortNameArr[33] = QString("Nahum");                           bookMinNameArr[33] = QString("Nahum");//Nah
  bookNameArr[34] = QString("Habacuc");                                 bookShortNameArr[34] = QString("Habacuc");                         bookMinNameArr[34] = QString("Hab");//Hab
  bookNameArr[35] = QString("Sofonías");                                bookShortNameArr[35] = QString("Sofonías");                        bookMinNameArr[35] = QString("Sof");//Sof
  bookNameArr[36] = QString("Hageo");                                   bookShortNameArr[36] = QString("Hageo");                           bookMinNameArr[36] = QString("Hageo");//Hag
  bookNameArr[37] = QString("Zacarías");                                bookShortNameArr[37] = QString("Zacarías");                        bookMinNameArr[37] = QString("Zac");//Zac
  bookNameArr[38] = QString("Malaquías");                               bookShortNameArr[38] = QString("Malaquías");                       bookMinNameArr[38] = QString("Mal");//Mal

  bookNameArr[39] = QString("3 Esdras");                                bookShortNameArr[39] = QString("3 Esdras");                        bookMinNameArr[39] = QString("3Esd");//3Esd
  bookNameArr[40] = QString("Tobit");                                   bookShortNameArr[40] = QString("Tobit");                           bookMinNameArr[40] = QString("Tobit");//Tb
  bookNameArr[41] = QString("Judit");                                   bookShortNameArr[41] = QString("Judit");                           bookMinNameArr[41] = QString("Judit");//Jdt
  bookNameArr[42] = QString("Sabiduría de Salomón");                    bookShortNameArr[42] = QString("Sabiduría");                       bookMinNameArr[42] = QString("Sab");//Sab
  bookNameArr[43] = QString("Sabiduría de Jesús ben Sira");             bookShortNameArr[43] = QString("Sirácida"); /*Eclesiástico*/       bookMinNameArr[43] = QString("Sirác");//Si  /*Eclo*/
  bookNameArr[44] = QString("Carta de Jeremías");                       bookShortNameArr[44] = QString("Carta de Jeremías");               bookMinNameArr[44] = QString("CtJer");//CtJ
  bookNameArr[45] = QString("Baruc");                                   bookShortNameArr[45] = QString("Baruc");                           bookMinNameArr[45] = QString("Baruc");//Bar
  bookNameArr[46] = QString("1 Macabeos");                              bookShortNameArr[46] = QString("1 Macabeos");                      bookMinNameArr[46] = QString("1Mac");//1Mac
  bookNameArr[47] = QString("2 Macabeos");                              bookShortNameArr[47] = QString("2 Macabeos");                      bookMinNameArr[47] = QString("2Mac");//2Mac
  bookNameArr[48] = QString("3,4 Macabeos");                            bookShortNameArr[48] = QString("3,4 Macabeos");                    bookMinNameArr[48] = QString("3,4Mac");//3,4Mac
  bookNameArr[49] = QString("4 Esdras");                                bookShortNameArr[49] = QString("4 Esdras");                        bookMinNameArr[49] = QString("4Esd");//4Esd

  bookNameArr[50] = QString("Evangelio de Mateo");                      bookShortNameArr[50] = QString("Mateo");                           bookMinNameArr[50] = QString("Mateo");//Mt
  bookNameArr[51] = QString("Evangelio de Marcos");                     bookShortNameArr[51] = QString("Marcos");                          bookMinNameArr[51] = QString("Marcos");//Mc
  bookNameArr[52] = QString("Evangelio de Lucas");                      bookShortNameArr[52] = QString("Lucas");                           bookMinNameArr[52] = QString("Lucas");//Lc
  bookNameArr[53] = QString("Evangelio de Juan");                       bookShortNameArr[53] = QString("Juan");                            bookMinNameArr[53] = QString("Juan");//Jn
  bookNameArr[54] = QString("Hechos de los Apóstoles");                 bookShortNameArr[54] = QString("Hechos");                          bookMinNameArr[54] = QString("Hechos");//Hch

  bookNameArr[55] = QString("Epístola a los Romanos");                  bookShortNameArr[55] = QString("Romanos");                         bookMinNameArr[55] = QString("Rom");//Rom
  bookNameArr[56] = QString("Primera Epístola a los Corintios");        bookShortNameArr[56] = QString("1 Corintios");                     bookMinNameArr[56] = QString("1Cor");//1Co
  bookNameArr[57] = QString("Segunda Epístola a los Corintios");        bookShortNameArr[57] = QString("2 Corintios");                     bookMinNameArr[57] = QString("2Cor");//2Co
  bookNameArr[58] = QString("Epístola a los Gálatas");                  bookShortNameArr[58] = QString("Gálatas");                         bookMinNameArr[58] = QString("Gálat");//Gl
  bookNameArr[59] = QString("Epístola a los Efesios");                  bookShortNameArr[59] = QString("Efesios");                         bookMinNameArr[59] = QString("Efes");//Ef
  bookNameArr[60] = QString("Epístola a los Filipenses");               bookShortNameArr[60] = QString("Filipenses");                      bookMinNameArr[60] = QString("Filip");//Flp
  bookNameArr[61] = QString("Epístola a los Colosenses");               bookShortNameArr[61] = QString("Colosenses");                      bookMinNameArr[61] = QString("Colos");//Col
  bookNameArr[62] = QString("Primera Epístola a los Tesalonicenses");   bookShortNameArr[62] = QString("1 Tesalonicenses");                bookMinNameArr[62] = QString("1Tes");//1Tes
  bookNameArr[63] = QString("Segunda Epístola a los Tesalonicenses");   bookShortNameArr[63] = QString("2 Tesalonicenses");                bookMinNameArr[63] = QString("2Tes");//2Tes
  bookNameArr[64] = QString("Primera Epístola a Timoteo");              bookShortNameArr[64] = QString("1 Timoteo");                       bookMinNameArr[64] = QString("1Tim");//1Tim
  bookNameArr[65] = QString("Segunda Epístola a Timoteo");              bookShortNameArr[65] = QString("2 Timoteo");                       bookMinNameArr[65] = QString("2Tim");//2Tim
  bookNameArr[66] = QString("Epístola a Tito");                         bookShortNameArr[66] = QString("Tito");                            bookMinNameArr[66] = QString("Tito");//Tit
  bookNameArr[67] = QString("Epístola a Filemón");                      bookShortNameArr[67] = QString("Filemón");                         bookMinNameArr[67] = QString("Filem");//Flm
  bookNameArr[68] = QString("Epístola a los Hebreos");                  bookShortNameArr[68] = QString("Hebreos");                         bookMinNameArr[68] = QString("Heb");//Heb

  bookNameArr[69] = QString("Epístola de Santiago");                    bookShortNameArr[69] = QString("Santiago");                        bookMinNameArr[69] = QString("Sant");//Stg
  bookNameArr[70] = QString("Primera Epístola de San Pedro");           bookShortNameArr[70] = QString("1 Pedro");                         bookMinNameArr[70] = QString("1Pedro");//1Pe
  bookNameArr[71] = QString("Segunda Epístola de San Pedro");           bookShortNameArr[71] = QString("2 Pedro");                         bookMinNameArr[71] = QString("2Pedro");//2Pe
  bookNameArr[72] = QString("Primera Epístola de San Juan");            bookShortNameArr[72] = QString("1 Juan");                          bookMinNameArr[72] = QString("1Juan");//1Jn
  bookNameArr[73] = QString("Segunda Epístola de San Juan");            bookShortNameArr[73] = QString("2 Juan");                          bookMinNameArr[73] = QString("2Juan");//2Jn
  bookNameArr[74] = QString("Tercera Epístola de San Juan");            bookShortNameArr[74] = QString("3 Juan");                          bookMinNameArr[74] = QString("3Juan");//3Jn
  bookNameArr[75] = QString("Epístola de San Judas");                   bookShortNameArr[75] = QString("Judas");                           bookMinNameArr[75] = QString("Judas");//Jud

  bookNameArr[76] = QString("Apocalipsis de San Juan");                 bookShortNameArr[76] = QString("Apocalipsis");                     bookMinNameArr[76] = QString("Apoc");//Ap
}
