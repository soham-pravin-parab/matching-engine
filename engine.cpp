
#include <iostream>
#include <map>
struct order{
int id;
char side;
double price;
int quantity;
order* next;
order* prev;
};
struct pricelevel{
double price;
order* head;
order* tail;
};
class OrderBook{
private:
std::map<double,pricelevel,std::greater<double>>bidBook;
std::map<double,pricelevel>askbook;
public:
void processorder(int id,char side,double price,int quantity){
   order* newOrder=new order();
   newOrder->id = id;
   newOrder->side = side;
   newOrder->price = price;
   newOrder->quantity = quantity;
   newOrder->prev = nullptr;
   newOrder->next = nullptr;

  if(side=='B'){
   while(!askbook.empty()&&newOrder->quantity>0){
     auto bestAskIt = askbook.begin();
     double bestAskPrice = bestAskIt->first;
     pricelevel& lowestAskLevel = bestAskIt->second;

    if(bestAskPrice<=newOrder->price){
     order* currentSeller=lowestAskLevel.head;

     while(currentSeller!=nullptr&&newOrder->quantity>0){
     int tradeQty = std::min(newOrder->quantity,currentSeller->quantity);
     newOrder->quantity -= tradeQty;
     currentSeller->quantity -= tradeQty;

     std::cout<<"Trade Executed! Price $ "<<bestAskPrice
              <<" |Quantity: "<<tradeQty<<std::endl;

    if(currentSeller==0){
   lowestAskLevel.head= currentSeller->next;
   currentSeller=lowestAskLevel.head;
}
}
if(lowestAskLevel.head==nullptr){
   askbook.erase(bestAskIt);
}
}
else{
break;
}
}
}

   else if (side=='S'){
    while(!bidBook.empty()&&newOrder->quantity>0){
    auto bestBidIt = bidBook.begin();
    double bestBidPrice = bestBidIt->first;
    pricelevel& highestBidLevel = bestBidIt->second;

    if(bestBidPrice>=newOrder->price){
      order* currentBuyer = highestBidLevel.head;
      while(currentBuyer!=nullptr && newOrder->quantity>0){
      int tradeQty = std::min(newOrder->quantity,currentBuyer->quantity);

     newOrder->quantity-= tradeQty;
     currentBuyer->quantity -= tradeQty;
     std::cout<<"TRADE EXECUTED! PASSED ORDER # "<<currentBuyer->id
     <<" | Price: $ "<<bestBidPrice
     <<" | Qty: "<<tradeQty<<std::endl;

     if(currentBuyer->quantity==0){
     highestBidLevel.head=currentBuyer->next;
     currentBuyer = highestBidLevel.head;
}
}
if(highestBidLevel.head==nullptr){
    bidBook.erase(bestBidIt);
}
}else{
break;
}
}
}

   if(side=='S'){
   pricelevel& level = askbook[price];
  level.price = price;

  if(level.head==nullptr){
   level.head=newOrder;
   level.tail=newOrder;

}
  else{
   level.tail->next = newOrder;
   newOrder->prev = level.tail;
   level.tail = newOrder;
}
   std::cout<<"sucessfully added Sell Order #"<<id<<" to the book"<<std::endl;
  }
  else if(side=='B'){
  pricelevel& level = bidBook[price];
  level.price = price;
  if(level.head==nullptr){
   level.head = newOrder ;
   level.tail = newOrder;

}
  else{
   level.tail->next = newOrder;
   newOrder->prev = level.tail;
   level.tail = newOrder;
}
std::cout<<"sucessfully added buyer #"<<id<<" to the book"<<std::endl;
}
}

void printBook(){
   std::cout<<"\n---CURRENT ORDER BOOK---"<<std::endl;
   std::cout<<"ASKS (Sellers):"<<std::endl;
   for(auto it= askbook.rbegin();it!=askbook.rend();it++){
   std::cout<<"PRICE: $"<<it->first<<" ->Orders: ";
   order* curr = it->second.head;
     while(curr){
   std::cout<<"["<<curr->id<<":"<<curr->quantity<<"]";
   curr = curr->next;
}
   std::cout<<std::endl;
}
   std::cout<<"BIDS(Buyers):"<<std::endl;
   for(const auto& pair : bidBook){
   std::cout<<" Price: $"<<pair.first<<" -> Orders: ";
   order* curr = pair.second.head;
   while(curr){
   std::cout<<"["<<curr->id<<": "<<curr->quantity<<"] ";
   curr = curr->next;
}
  std::cout<<std::endl;
}
std::cout<<"–-----------------------------------------\n"<<std::endl;

}


};
int main(){
OrderBook book;
book.processorder(1,'S',10.5,100);
book.processorder(2,'B',9.5,50);
return 0;
}



