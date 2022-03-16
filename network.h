#include<math.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
#include<ctime>
using namespace std;
string dec_to_base( int n, int base ) {
	const string chars = "0123456789abcdef";
	return n < base ? chars.substr( n, 1 ) : dec_to_base( n / base, base ) + chars[n%base];
}
void print_IP(int a[]){
	for(int i=0;i<4;i++){
		cout << a[i];
		if(i!=3) cout << '.';
	}
	cout << endl;
} 
inline int get_prefix_from_class(char Cl) {
	if(Cl=='A') return 8;
	if(Cl=='B') return 16;
	if(Cl=='C') return 24;
}
inline int ascii_to_int(int q) {
	if(q>47 && q<58) return q-48;
	if(q>64 && q<71) return q-55;
	if(q>96 && q<103) return q-87;
}
int base_to_dec(string s,int base) {
	if(s[0]==45) s.erase(0,1);
	int k=0;
	for(int i=s.length()-1,count=0; i>=0; i--,count++) k+=ascii_to_int(s[i])*pow(base,count);
	return k;
}
void print_in_bits(int dec,int bits,int base) {
	string s=dec_to_base(abs(dec),base);
	if(bits!=0 && s.length()%bits!=0) for(int i=bits-(s.length()%bits); i>0; i--) s = '0' + s;
	printf("He %-2d : ",base);
	if(dec<0) cout << "- ";
	for(int i=0; i<s.length(); i++) {
		cout << s[i];
		if(bits!=0) if((i+1)%bits==0) cout <<" ";
	}
	cout << '\n';
}
bool Invalid_base(string x,int base) {
	if(base<=0) return false;
	if(x[0]==45) x.erase(0,1);
	for(int i=0; i<x.length(); i++) if(ascii_to_int(x[i])>base) return false;
	return true;
}
void base_converter() {
	int dec,bits,base;
	string x;
	cout << "Nhap x: ";
	cin >> x;
	cout << "He so cua x: ";
	cin >> base;
	if(!Invalid_base(x,base)) {
		system("cls");
		cout << "Nhap du lieu khong hop le !\n";
		return ;
	}
	cout << "So bit gian cach ?(nhap 0 de bo qua): ";
	cin >> bits;
	dec=base_to_dec(x,base);
	if(x[0]==45) dec*=-1;
	system("cls");
	cout << "Gia tri da nhap: " << x << "(" << base << ")" << endl;
	print_in_bits(dec,bits,2);
	print_in_bits(dec,bits,8);
	print_in_bits(dec,bits,10);
	print_in_bits(dec,bits,16);
}
void print_hexa_IPv6(string s) {
	for(int i=0; i<s.length(); i++) {
		if(s[i]!='0') {
			for(int j=i; j<s.length(); j++) {
				cout << s[j];
			}
			return ;
		}
	}
	if(s.length()==1 && s[0]=='0');
	cout << '0';
}
string oct_hexa(int x) {
	string s=dec_to_base(x,16);
	return (s.length()==1 && s.length()!=0) ? '0'+s : s;
}
void IPv4_IPv6 () {
	cout << "Nhap IPv4 theo dinh dang: A B C D "<< endl;
	cout << "Vi du: " << "172.254.16.33" << " Nhap: 172 254 16 33" << endl;
	int x1,x2,x3,x4;
	cin >> x1 >> x2 >> x3 >> x4;
	string s1=oct_hexa(x1),s2=oct_hexa(x2),s3=oct_hexa(x3),s4=oct_hexa(x4);
	s1+=s2;
	s3+=s4;
	system("cls");
	cout <<"IPv4: " << x1 << '.' << x2 << '.'<< x3 << '.' << x4 << endl;
	cout <<"Chuyen sang IPv6 la:\n";
	cout <<"::ffff:";
	print_hexa_IPv6(s1);
	cout << ":";
	print_hexa_IPv6(s3);
	cout << endl;
}
inline bool Invalid_IPv4(int a[]) {
	for(int i=0; i<3; i++) if(a[i]<0 || a[i]>255) return false;
	return true;
}
inline int get_streak(int x) {
	if(x>=8) return 8;
	if(x<=0) return 0;
	return x;
}
int count_1(int x) {
	int count=0;
	for(int i=8; i>=0; i--) {
		if(pow(2,i)<=x) {
			count ++;
			x-=pow(2,i);
		}
	}
	return count;
}
int octet_cvt(int x,int length,int bit) {
	int k=7;
	int bin[8]= {0};
	while(x!=0) {
		bin[k]=x%2;
		x/=2;
		k--;
	}
	for(int i=length; i<8; i++) bin[i]=bit;
	for(int i=0; i<8; i++) x+=bin[i]*(pow(2,7-i));
	return x;
}
inline bool isPublic(int a,int b) {
	if(a==10 || a==127) return false;
	if(a==172 && b>15 && b<32) return false;
	if(a==192 && b==168) return false;
	if(a==169 && b==254) return false;
	return true;
}
inline int streak_1_to_dec(int x) {
	if(x<=0) return 0;
	int k=0;
	for(int i=1; i<=x; i++) k+= pow(2,8-i);
	return k;
}
void mask_to_prefix(int *a,int *b) {
	if(a[0]==-1) return ;
	*b=(count_1(a[0]) + count_1(a[1]) + count_1(a[2]) + count_1(a[3]));
}
void Calculate_Packet() {
	float Packet_size,MTU;
	int t;
	cout << "Nhap dung luong goi: ";
	cin >> Packet_size;
	system("cls");
	cout << "Nhap MTU: ";
	cin >> MTU;
	system("cls");
	cout << "1.UDP\n2.TCP\n3.Bo qua\n";
	t=getch()-48;
	if(t==1) MTU-=8;
	if(t==2) MTU-=20;
	system("cls");
	cout << "1.IPv4\n2.IPv6\n3.Bo qua\n";
	t=getch()-48;
	if(t==1) MTU-=20;
	if(t==2) MTU-=40;
	system("cls");
	cout << "Ket qua: ";
	if(Packet_size/MTU==(int)(Packet_size/MTU)) cout << (int)(Packet_size/MTU) << endl;
	else cout << (int)(Packet_size/MTU+1) << endl;
}
inline int get_prf(int x) {
	for(int i=25; i>=0; i--) if(pow(2,i)<(x+2)) return 31-i;
}
void fit_mask() {
	cout <<"Nhap so host: ";
	int x;
	cin >> x;
	if(x>=4194304 || x<=0) {
		cout << "\nGia tri nhap vao khong hop le!\n0 < Host < 2^22(4194304)\n";
		return ;
	}
	x=get_prf(x);
	cout << "Prefix toi uu: " << x << endl;
	cout << "\nDia chi IP: x1.x2.x3.x4\n";
	int tA=x-get_prefix_from_class('A'),tB=x-get_prefix_from_class('B'),tC=x-get_prefix_from_class('C');
	if(tA>0) cout << "Class A(x1: 000-127): can muon them " << tA << " bit "<< endl;
	if(tB>0) cout << "Class B(x1: 128-191): can muon them " << tB << " bit "<< endl;
	if(tC>0) cout << "Class C(x1: 192-224): can muon them " << tC << " bit "<< endl;
	cout <<"\nMat na mang toi uu: ";
	for(int i=0; i<4; i++) {
		cout << streak_1_to_dec(get_streak(x));
		x-=8;
		if(i!=3)cout << '.';
	}
	cout << endl;
}
void Choice() {
	system("cls");
	/*	cout <<"Lua chon:\n" << "1.Tinh toan IP\n" << "2.Tinh thoi gian truyen goi tin\n" ;
		cout <<"3.Tinh throughput\n" << "4.Chuyen he co so\n" << "5.Mat na mang toi uu\n" ;
		cout <<"6.Doi IPv4 sang IPv6\n" << "7.Gia tri hieu so cong hop le trong TCP/IP\n" ; */
	cout << "|---------------------------------------------------|" << endl ;
	cout << "|--  Phim  ----------Tinh nang------------  Token --|" << endl ;
	cout << "|--   1    --    Tinh toan IP  	        --   03   --|" << endl ;
	cout << "|--   2    --    T/g truyen goi tin     --   05   --|" << endl ;
	cout << "|--   3    --    Tinh toan throughput   --   10   --|" << endl ;
	cout << "|--   4    --    Chuyen doi he co so	--   01   --|" << endl ;
	cout << "|--   5    --    Mat na mang toi uu     --   05   --|" << endl ;
	cout << "|--   6    --    Doi IPv4 sang IPv6	--   07   --|" << endl ;
	cout << "|--   7    --    Hieu so cong hop le    --   00   --|" << endl ;
	cout << "|---------------------------------------------------|" << endl ;
}
void lib_input_ip(int *oct) {
	system("cls");
	cout << "Dinh dang: A B C D "<< endl;
	cout << "Vi du: " << "172.254.16.33" << " Nhap: 172 254 16 33" << endl;
	cin >> oct[0] >> oct[1] >> oct[2] >> oct[3];
	system("cls");
}
void Throughput_Calculator() {
	float RTT,windows_size,throughput;
	cout << "Nhap RTT (ms): ";
	cin >> RTT;
	cout << "Nhap kich thuoc cua so: ";
	cin >> windows_size;
	throughput = windows_size / (RTT*0.001);
	system("cls");
//	cout << "Throughput: " << throughput << endl;
	cout << "Ket qua: " << (int)throughput << " (su dung ket qua lam tron xuong)\n";
	cout << "Duong truyen vat ly khong anh huong ket qua\n";
}
void valid_port_number() {
	system("cls");
	cout << "Gia tri hieu so cong x hop le khi:\n";
	cout << "0 <= x <= 65535 (2^16-1)\n";
}
inline int choose(int x) {
	if(x==0) return 33;
	if(x==1) return 65;
	return 97;
}

int q1(int x) {
	if(x>96) return 97;
	if(x>64) return 65;
	return 33;
}

void toClipboard(const string &s) {
	HWND hwnd = GetDesktopWindow();
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}
void gettime(int *days,int *hours,int *minutes, int *seconds) {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	*days    = ltm->tm_mday;
	*hours   = ltm->tm_hour;
	*minutes = ltm->tm_min ;
	*seconds = ltm->tm_sec ;
}
int totalsecond(int hours,int minutes, int seconds) {
	return ((hours*3600)+(minutes*60)+minutes);
}
