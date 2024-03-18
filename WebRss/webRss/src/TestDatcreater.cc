#include"../include/Datcreater.h"
int main(){
    Datcreater datc;
datc.setFilenames();
datc.HandleAllFile();
cout<<"HandleAllFile complete"<<endl;
cout<<"InvertIndex iid;"<<endl;
InvertIndex iid;
cout<<"start gen webitem"<<endl;
iid.getwebitem();
cout<<"webitem generated"<<endl;
cout<<"start gen worditem"<<endl;
iid.readFile();
cout<<"worddic gened"<<endl;
cout<<"gen InvertIndex"<<endl;
iid.geninvertindexitem();
cout<<"InvertIndex gened"<<endl;
iid.WriteInvert();
cout<<"InvertIndex write down"<<endl;

return 0;
}
