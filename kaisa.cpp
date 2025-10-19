#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class  Crypto {
    private:
        int key;
        string code;

    public:
    void set(int k, string c){
        key = k;
        code = c;
    }
    string jiami(){
        string result;
        for(char c : code){
            if(c>='a' && c<='z'){
                result += (char)((c - 'a' + key) % 26 + 'a');
            }
            else if(c>='A' && c<='Z'){
                result += (char)((c - 'A' + key) % 26 + 'A');
            }
            else result +=c;
        }
        return result;
    }
    string jiemi(){
         string result;
        for(char c : code){
            if(c>='a' && c<='z'){
                result += (char)((c - 'a' - key+26) % 26 + 'a');
            }
            else if(c>='A' && c<='Z'){
                result += (char)((c - 'A' - key+26) % 26 + 'A');
            }
            else result +=c;
        }
        return result;
    }
};



class FileHandler{
    private:
    string path;
    public:
    void setpath(string p){
        path=p;
    }
    string read(){
        ifstream s1(path);
        string context;
        string line;
        while(getline(s1,line)){
            context+=line+"\n";
        }
        s1.close();
        return context;
    }
    void write(string str,string pa){
        ofstream s2(pa);
        s2<<str;
        s2.close();
    }


    
};





class Menu{

    public:
    void display(){
        cout<<"菜单"<<endl;
        cout<<"1.加密"<<endl;
        cout<<"2.解密"<<endl;
        cout<<"3.文件加密"<<endl;
        cout<<"4.文件解密"<<endl;
        cout<<"0.退出"<<endl;
        cout<<"请输入选项(0~4)："<<endl;
    }
    void go(){
        int flag=true;
        int choice;
        while(flag){
            display();
            cin>>choice;
            cin.ignore();
            switch(choice){
                case 1:{
                    cout<<"请输入要加密的文本："<<endl;
                    string c1;
                    getline(cin,c1);
                    cout<<"请输入密钥："<<endl;
                    int k1;
                    cin>>k1;
                    cin.ignore();
                    Crypto crypto1;
                    crypto1.set(k1,c1);
                    string result=crypto1.jiami();
                    cout<<"加密后的文本为："<<result<<endl;
                    break;
                }
                case 2:{
                    cout<<"请输入要解密的文本："<<endl;
                    string c2;
                    getline(cin,c2);
                    cout<<"请输入密钥："<<endl;
                    int k2;
                    cin>>k2;    
                    Crypto crypto2;
                    crypto2.set(k2,c2);
                    string result2=crypto2.jiemi();
                    cout<<"解密后的文本为："<<result2<<endl;
                    break;
                }
                case 3:{
                    cout<<"请输入要加密的文件路径：";
                    string path1;
                    cin>>path1;
                    int k3;
                    cout<<"请输入密钥：";
                    cin>>k3;
                    cin.ignore();
                    FileHandler filehandler1;
                    filehandler1.setpath(path1);
                    string news1= filehandler1.read();
                    Crypto crypto3;
                    crypto3.set(k3,news1);
                    string result3=crypto3.jiami();
                    filehandler1.write(result3,"/home/ep/桌面/凯撒/encrypted.txt");
                    cout<<"加密结果已保存到:encrypted.txt"<<endl;
                    break;}
                case 4:{
                    cout<<"请输入要解密的文件路径：";
                    string path2;
                    cin>>path2;
                    int k4;
                    cout<<"请输入密钥：";
                    cin>>k4;
                    cin.ignore();
                    FileHandler filehandler2;
                    filehandler2.setpath(path2);
                    string news2= filehandler2.read();
                    Crypto crypto4;
                    crypto4.set(k4,news2);
                    string result4=crypto4.jiemi();
                    filehandler2.write(result4,"/home/ep/桌面/凯撒/decrypted.txt");
                    cout<<"解密结果已保存到:decrypted.txt"<<endl;
                    break;
                }
                
                case 0:{
                    cout<<"退出力！";
                    flag=false;
                }
                
            }
        }

    } 
};

int main(){
    Menu menu;
    menu.go();
    return 0;
}