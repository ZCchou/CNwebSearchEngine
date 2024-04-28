#include "Diccreater.cc"
#include "JsonReader.cc"
#include<iostream>
int main(){
Diccreater datc;
cout<<"setFilenames"<<endl;
datc.setFilenames();
cout<<"setFilenames complete"<<endl<<endl;
cout<<"HandleAllFile"<<endl;
datc.HandleAllFile();
cout<<"HandleAllFile complete"<<endl;

return 0;
}
