

/*
 Assignment: Assignment 6 - Quadratic Probing with a find()
 File - main.cpp
 Developer:  Matthew Bozelka
 Teacher: Anand Venkataraman
 Program purpose: Testing of Quadratic Probing.
 */

#include <iostream>
#include "EBookEntry.h"
using namespace std;

// prototyping of Hash functions and FHhashQPwFind include
int Hash( int key );
int Hash( const string & key );
int Hash( const EBookEntry & item );
#include "FHhashQPwFind.h"

// prototyping of getKey functions
int getKey( const EBookEntry & item);
//string getKey( const EBookEntry & item);

// prototyping of helper functions
int randomNum(const int & generateBetween);
void displayOneEBook(EBookEntry book);




int main(int argc, const char * argv[]) {

   // read eBook the data
   EBookEntryReader bookInput("catalog-short4.txt");
   if (bookInput.readError())
   {
      cout << "couldn't open " << bookInput.getFileName()
           << " for input.\n";
      exit(1);
   }

   FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
   //FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

   // we want two books to be identical in different ways: ID or author
   EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
   //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);
   const int NUM_RANDOM_INDICES = 25;
   int bookCount = bookInput.getNumBooks(), randomIndices[NUM_RANDOM_INDICES];

   cout << bookInput.getFileName() << endl;
   cout << bookCount << endl << endl;

   // generate random indices
   for(int k = 0; k < NUM_RANDOM_INDICES; k++)
      randomIndices[k] = randomNum(bookCount);

   // insert ALL eBooks into the hash table
   for(int k = 0; k < bookCount; k++)
      hashTable.insert(bookInput[k]);

   cout << "* original eBook array *\n\n";

   // Display 25 eBooks from the EBookEntryReader array at random indices
   for(int k = 0; k < NUM_RANDOM_INDICES; k++)
      displayOneEBook(bookInput[randomIndices[k]]);

   // attempt to find on the selected key
   cout << "* The same random books displayed from the hash table *\n\n";
   for (int k = 0; k < NUM_RANDOM_INDICES; k++)
   {
      try
      {
         EBookEntry book;
         book = hashTable.find(bookInput[ randomIndices[k] ].getETextNum());
         //book = hashTable.find(bookInput[ randomIndices[k] ].getCreator());
         displayOneEBook(book);
      }
      catch (...)
      {
         cout << "no match found.\n";
      }
      cout << endl;
   }


   // test known failures exceptions:
   cout << "Test Try/Catch with unknowns.\n";
   try
   {
      EBookEntry book;
      book = hashTable.find( -3 );
      //book = hashTable.find( "Jack Kerouac" );
      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "no match found.\n";
   }

   try
   {
      EBookEntry book;
      book = hashTable.find( -7 );
      //book = hashTable.find( "George R. R. Martin" );
      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "no match found.\n";
   }

   try
   {
      EBookEntry book;
      book = hashTable.find( -10 );
      //book = hashTable.find( "Gillian Flynn" );
      displayOneEBook(book);
   }
   catch (...)
   {
      cout << "no match found.\n";
   }

   return 0;
}




// helper function to find random int
int randomNum(const int & generateBetween)
{

   srand (time(NULL) + rand( ));
   return rand() % generateBetween;

}




// helper function to display an eBook
void displayOneEBook(EBookEntry book)
{
   cout << "# "<< book.getETextNum() << "  ---------------" << endl
        << "\"" << book.getTitle() <<"\"" << endl
        << "by " << book.getCreator()  << endl
        << "re: " << book.getSubject() << endl << endl;
}





// used for author equality
//string getKey( const EBookEntry & item )
//{
//   return item.getCreator() ;
//}



// used for ID equality
int getKey( const EBookEntry & item)
{
   return item.getETextNum() ;
}



/************ hash functions *****************/

// a hash routine for ints
int Hash( int key )
{
   return key;
}

// a hash routine for strings that admits negative returns
int Hash( const string & key )
{
   unsigned int k, retVal = 0;

   for(k = 0; k < key.length( ); k++ )
      retVal = 37 * retVal + key[k];

   return retVal;
}


int Hash( const EBookEntry & item )
{
   return Hash(getKey(item));
}


// test outputs

// test with Hash int
/*
 catalog-short4.txt
 550

 * original eBook array *

 # 27623  ---------------
 "C'est la loi!"
 by Du Veuzit, Max, 1886-1952
 re: French drama -- 20th century

 # 25390  ---------------
 "Tabitha at Ivy Hall"
 by Brown, Ruth Alberta
 re: Friendship -- Juvenile fiction

 # 25626  ---------------
 "The Girl Scouts at Bellaire
 Or Maid Mary's Awakening"
 by Garis, Lilian, 1873-1954
 re: Vacations -- Juvenile fiction

 # 2274  ---------------
 "How to Live on 24 Hours a Day"
 by Bennett, Arnold, 1867-1931
 re: Conduct of life

 # 27419  ---------------
 "Barnavännen, 1905-04
 Illustrerad Veckotidning för de Små"
 by Various
 re: Svenska missionsförbundet -- Periodicals

 # 29824  ---------------
 "Diana"
 by Warner, Susan, 1819-1885
 re: Women -- New England -- Fiction

 # 29542  ---------------
 "The Valor of Cappen Varra"
 by Anderson, Poul William, 1926-2001
 re: Short stories

 # 216  ---------------
 "The Tao Teh King, or the Tao and its Characteristics"
 by Laozi
 re: Taoism

 # 26026  ---------------
 "The Surrender of Santiago
 An Account of the Historic Surrender of Santiago to General
 Shafter, July 17, 1898"
 by Norris, Frank, 1870-1902
 re: Spanish-American War, 1898 -- Campaigns

 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy

 # 25346  ---------------
 "Nan Qiang Bei Diao Ji"
 by Lu, Xun, 1881-1936
 re: PL

 # 24994  ---------------
 "Wheat Growing in Australia"
 by Australia. Dept. of External Affairs
 re: Wheat -- Australia

 # 28476  ---------------
 "Notes and Queries, Number 194, July 16, 1853
 A Medium of Inter-communication for Literary Men, Artists,
 Antiquaries, Genealogists, etc"
 by Various
 re: Questions and answers -- Periodicals

 # 29468  ---------------
 "The Story of Don Quixote"
 by Cervantes Saavedra, Miguel de, 1547-1616
 re: Spain -- Social life and customs -- 16th century -- Fiction

 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy

 # 25028  ---------------
 "Heist Job on Thizar"
 by Garrett, Randall, 1927-1987
 re: Short stories

 # 27785  ---------------
 "A Book About Lawyers"
 by Jeaffreson, John Cordy, 1831-1901
 re: Lawyers -- Great Britain -- Anecdotes

 # 28792  ---------------
 "Omnilingual"
 by Piper, H. Beam, 1904-1964
 re: Science fiction

 # 24887  ---------------
 "Ulrich Schmidel
 Der erste Geschichtschreiber der La Plata-Länder (1535-1555)"
 by Lehmann-Nitsche, Robert, 1872-1938
 re: Biography

 # 30072  ---------------
 "Angelot
 A Story of the First Empire"
 by Price, Eleanor C. (Eleanor Catherine)
 re: Napoleonic Wars, 1800-1815 -- Fiction

 # 30036  ---------------
 "Word Study and English Grammar
 A Primer of Information about Words, Their Relations and Their Uses"
 by Hamilton, Frederick W. (Frederick William), 1860-1940
 re: English language -- Grammar

 # 29165  ---------------
 "The American Missionary — Volume 38, No. 01, January, 1884"
 by Various
 re: Congregational churches -- Missions -- Periodicals

 # 12107  ---------------
 "The Atlantic Monthly, Volume 09, No. 55, May, 1862"
 by Various
 re: AP

 # 27159  ---------------
 "Due amori"
 by Farina, Salvatore, 1846-1918
 re: PQ

 # 29042  ---------------
 "A Tangled Tale"
 by Carroll, Lewis, 1832-1898
 re: Mathematical recreations

 * The same random books displayed from the hash table *

 # 27623  ---------------
 "C'est la loi!"
 by Du Veuzit, Max, 1886-1952
 re: French drama -- 20th century


 # 25390  ---------------
 "Tabitha at Ivy Hall"
 by Brown, Ruth Alberta
 re: Friendship -- Juvenile fiction


 # 25626  ---------------
 "The Girl Scouts at Bellaire
 Or Maid Mary's Awakening"
 by Garis, Lilian, 1873-1954
 re: Vacations -- Juvenile fiction


 # 2274  ---------------
 "How to Live on 24 Hours a Day"
 by Bennett, Arnold, 1867-1931
 re: Conduct of life


 # 27419  ---------------
 "Barnavännen, 1905-04
 Illustrerad Veckotidning för de Små"
 by Various
 re: Svenska missionsförbundet -- Periodicals


 # 29824  ---------------
 "Diana"
 by Warner, Susan, 1819-1885
 re: Women -- New England -- Fiction


 # 29542  ---------------
 "The Valor of Cappen Varra"
 by Anderson, Poul William, 1926-2001
 re: Short stories


 # 216  ---------------
 "The Tao Teh King, or the Tao and its Characteristics"
 by Laozi
 re: Taoism


 # 26026  ---------------
 "The Surrender of Santiago
 An Account of the Historic Surrender of Santiago to General
 Shafter, July 17, 1898"
 by Norris, Frank, 1870-1902
 re: Spanish-American War, 1898 -- Campaigns


 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy


 # 25346  ---------------
 "Nan Qiang Bei Diao Ji"
 by Lu, Xun, 1881-1936
 re: PL


 # 24994  ---------------
 "Wheat Growing in Australia"
 by Australia. Dept. of External Affairs
 re: Wheat -- Australia


 # 28476  ---------------
 "Notes and Queries, Number 194, July 16, 1853
 A Medium of Inter-communication for Literary Men, Artists,
 Antiquaries, Genealogists, etc"
 by Various
 re: Questions and answers -- Periodicals


 # 29468  ---------------
 "The Story of Don Quixote"
 by Cervantes Saavedra, Miguel de, 1547-1616
 re: Spain -- Social life and customs -- 16th century -- Fiction


 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy


 # 25028  ---------------
 "Heist Job on Thizar"
 by Garrett, Randall, 1927-1987
 re: Short stories


 # 27785  ---------------
 "A Book About Lawyers"
 by Jeaffreson, John Cordy, 1831-1901
 re: Lawyers -- Great Britain -- Anecdotes


 # 28792  ---------------
 "Omnilingual"
 by Piper, H. Beam, 1904-1964
 re: Science fiction


 # 24887  ---------------
 "Ulrich Schmidel
 Der erste Geschichtschreiber der La Plata-Länder (1535-1555)"
 by Lehmann-Nitsche, Robert, 1872-1938
 re: Biography


 # 30072  ---------------
 "Angelot
 A Story of the First Empire"
 by Price, Eleanor C. (Eleanor Catherine)
 re: Napoleonic Wars, 1800-1815 -- Fiction


 # 30036  ---------------
 "Word Study and English Grammar
 A Primer of Information about Words, Their Relations and Their Uses"
 by Hamilton, Frederick W. (Frederick William), 1860-1940
 re: English language -- Grammar


 # 29165  ---------------
 "The American Missionary — Volume 38, No. 01, January, 1884"
 by Various
 re: Congregational churches -- Missions -- Periodicals


 # 12107  ---------------
 "The Atlantic Monthly, Volume 09, No. 55, May, 1862"
 by Various
 re: AP


 # 27159  ---------------
 "Due amori"
 by Farina, Salvatore, 1846-1918
 re: PQ
 
 
 # 29042  ---------------
 "A Tangled Tale"
 by Carroll, Lewis, 1832-1898
 re: Mathematical recreations
 
 
 Test Try/Catch with unknowns.
 no match found.
 no match found.
 no match found.
 Program ended with exit code: 0
 */


// test with Hash string
/*
 catalog-short4.txt
 550

 * original eBook array *

 # 28087  ---------------
 "Tuskegee &amp; Its People: Their Ideals and Achievements"
 by Campbell, Helen, 1839-1918
 re: Tuskegee Institute

 # 26997  ---------------
 "Chao Ye Qian Zai"
 by Zhang, Zhuo, ca. 660-ca. 740
 re: China -- History -- Tang dynasty, 618-907

 # 29517  ---------------
 "John and Betty's History Visit"
 by Williamson, Margaret, 1886-
 re: England -- Description and travel

 # 26302  ---------------
 "The Theory of Social Revolutions"
 by Adams, Brooks, 1848-1927
 re: Revolutions

 # 25346  ---------------
 "Nan Qiang Bei Diao Ji"
 by Lu, Xun, 1881-1936
 re: PL

 # 29405  ---------------
 "The Gods of Mars"
 by Burroughs, Edgar Rice, 1875-1950
 re: Science fiction

 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy

 # 18429  ---------------
 "Zonnestralen in School en Huis"
 by Dietz, Henriette
 re: Children's stories, Dutch

 # 25590  ---------------
 "Saru no ikigimo. English"
 by Chamberlain, Basil Hall, 1850-1935
 re: Fairy tales -- Japan

 # 29598  ---------------
 "Four Little Blossoms at Brookside Farm"
 by Hawley, Mabel C.
 re: PZ

 # 26785  ---------------
 "Modern British Poetry"
 by Euripides, 480? BC-406 BC
 re: English poetry -- 19th century

 # 24949  ---------------
 "Control Group"
 by Aycock, Roger D., 1914-2004
 re: Short stories

 # 25512  ---------------
 "The Fables of Phædrus
 Literally translated into English prose with notes"
 by Phaedrus
 re: Fables, Latin -- Translations into English

 # 25843  ---------------
 "The comedy of errors. Dutch"
 by Shakespeare, William, 1564-1616
 re: Comedies

 # 29420  ---------------
 "American Rural Highways"
 by Agg, T. R. (Thomas Radford), 1878-1947
 re: Roads -- United States

 # 29300  ---------------
 "Rodney The Partisan"
 by Castlemon, Harry, 1842-1915
 re: United States -- History -- Civil War, 1861-1865 -- Juvenile fiction

 # 28394  ---------------
 "William Penn"
 by Hodges, George, 1856-1919
 re: Penn, William, 1644-1718

 # 134  ---------------
 "Maria, or the Wrongs of Woman"
 by Wollstonecraft, Mary, 1759-1797
 re: Fiction

 # 19572  ---------------
 "Absolute Surrender and Other Addresses"
 by Murray, Andrew, 1828-1917
 re: Christian life

 # 26740  ---------------
 "The Picture of Dorian Gray"
 by Wilde, Oscar, 1854-1900
 re: Didactic fiction

 # 26740  ---------------
 "The Picture of Dorian Gray"
 by Wilde, Oscar, 1854-1900
 re: Didactic fiction

 # 27609  ---------------
 "The Undersea Tube"
 by Hansen, L. Taylor (Lucile Taylor), 1897-1976
 re: Science fiction

 # 27293  ---------------
 "A sketch of the life and services of Gen. Otho Holland Williams
 Read before the Maryland historical society, on Thursday
 evening, March 6, 1851"
 by Tiffany, Osmond, 1823-
 re: United States -- History -- Revolution, 1775-1783 -- Personal narratives

 # 29714  ---------------
 "The Negro Farmer"
 by Kelsey, Carl, 1870-1953
 re: African American farmers -- Southern States

 # 28065  ---------------
 "The Pecan and its Culture"
 by Hume, H. Harold (Hardrada Harold), 1875-1965
 re: Pecan

 * The same random books displayed from the hash table *

 # 28087  ---------------
 "Tuskegee &amp; Its People: Their Ideals and Achievements"
 by Campbell, Helen, 1839-1918
 re: Tuskegee Institute


 # 26997  ---------------
 "Chao Ye Qian Zai"
 by Zhang, Zhuo, ca. 660-ca. 740
 re: China -- History -- Tang dynasty, 618-907


 # 29517  ---------------
 "John and Betty's History Visit"
 by Williamson, Margaret, 1886-
 re: England -- Description and travel


 # 26302  ---------------
 "The Theory of Social Revolutions"
 by Adams, Brooks, 1848-1927
 re: Revolutions


 # 25346  ---------------
 "Nan Qiang Bei Diao Ji"
 by Lu, Xun, 1881-1936
 re: PL


 # 363  ---------------
 "The Oakdale Affair"
 by Burroughs, Edgar Rice, 1875-1950
 re: Fiction


 # 27368  ---------------
 "The Cult of Incompetence"
 by Faguet, Émile, 1847-1916
 re: Democracy


 # 18429  ---------------
 "Zonnestralen in School en Huis"
 by Dietz, Henriette
 re: Children's stories, Dutch


 # 25590  ---------------
 "Saru no ikigimo. English"
 by Chamberlain, Basil Hall, 1850-1935
 re: Fairy tales -- Japan


 # 29598  ---------------
 "Four Little Blossoms at Brookside Farm"
 by Hawley, Mabel C.
 re: PZ


 # 26785  ---------------
 "Modern British Poetry"
 by Euripides, 480? BC-406 BC
 re: English poetry -- 19th century


 # 24949  ---------------
 "Control Group"
 by Aycock, Roger D., 1914-2004
 re: Short stories


 # 25512  ---------------
 "The Fables of Phædrus
 Literally translated into English prose with notes"
 by Phaedrus
 re: Fables, Latin -- Translations into English


 # 1779  ---------------
 "The Merchant of Venice"
 by Shakespeare, William, 1564-1616
 re: Comedies


 # 29420  ---------------
 "American Rural Highways"
 by Agg, T. R. (Thomas Radford), 1878-1947
 re: Roads -- United States


 # 29300  ---------------
 "Rodney The Partisan"
 by Castlemon, Harry, 1842-1915
 re: United States -- History -- Civil War, 1861-1865 -- Juvenile fiction


 # 28394  ---------------
 "William Penn"
 by Hodges, George, 1856-1919
 re: Penn, William, 1644-1718


 # 134  ---------------
 "Maria, or the Wrongs of Woman"
 by Wollstonecraft, Mary, 1759-1797
 re: Fiction


 # 19572  ---------------
 "Absolute Surrender and Other Addresses"
 by Murray, Andrew, 1828-1917
 re: Christian life


 # 29208  ---------------
 "Salome en Een Florentijnsch Treurspel"
 by Wilde, Oscar, 1854-1900
 re: Salome (Biblical figure) -- Drama


 # 29208  ---------------
 "Salome en Een Florentijnsch Treurspel"
 by Wilde, Oscar, 1854-1900
 re: Salome (Biblical figure) -- Drama


 # 27609  ---------------
 "The Undersea Tube"
 by Hansen, L. Taylor (Lucile Taylor), 1897-1976
 re: Science fiction


 # 27293  ---------------
 "A sketch of the life and services of Gen. Otho Holland Williams
 Read before the Maryland historical society, on Thursday
 evening, March 6, 1851"
 by Tiffany, Osmond, 1823-
 re: United States -- History -- Revolution, 1775-1783 -- Personal narratives


 # 29714  ---------------
 "The Negro Farmer"
 by Kelsey, Carl, 1870-1953
 re: African American farmers -- Southern States
 
 
 # 28065  ---------------
 "The Pecan and its Culture"
 by Hume, H. Harold (Hardrada Harold), 1875-1965
 re: Pecan
 
 
 Test Try/Catch with unknowns.
 no match found.
 no match found.
 no match found.
 Program ended with exit code: 0
 */

