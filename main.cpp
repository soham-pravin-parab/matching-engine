#include "OrderBook.h"

int main(){
   OrderBook book;
   std::cout<<"Placing resting Limit orders . . . "<<std::endl;
   book.processorder(1,'S',105.0,10);
   book.processorder(2,'B',100.0,5);

   std::cout<<"Placing an agressive market/limit order at $106"<<std::endl;
   book.processorder(3,'B',106.0,7);
   book.printBook();

   return 0;
}
