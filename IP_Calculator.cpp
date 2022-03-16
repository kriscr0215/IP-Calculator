#include<iostream>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<network.h>
#include<conio.h>
using namespace std;
class IP_Calculator {
	private:
		char Class;
		int prefix,subnet_bits;
		int oct[4],network_adr[4],subnet_mask[4],broadcast_address[4];
	public:
		IP_Calculator();
		void input_ip();
		bool check_error();
		void input_prefix();
		void input_mask();
		void input_subnet();
		void set_class();
		void set_prefix();
		void set_address();
		void set_netmask();
		void sync_data();
		void print_data();
};
IP_Calculator::IP_Calculator() {
	prefix = subnet_bits = -1;
	Class = 'I';
	oct[4] = network_adr[4] = subnet_mask[4] = broadcast_address[4] = {-1};
}
void IP_Calculator::input_ip() {
	lib_input_ip(oct);
	set_class();
	set_prefix();
}
void IP_Calculator::input_prefix() {
	cout << "Nhap prefix: ";
	cin >> prefix;
}
void IP_Calculator::input_subnet() {
	system("cls");
	cout << "Nhap so bit muon them: ";
	cin >> subnet_bits;
	prefix+=subnet_bits;
}
void IP_Calculator::input_mask() {
	system("cls");
	cout <<"Dinh dang: A B C D" << endl;
	cout << "Nhap mat na mang: ";
	cin >> subnet_mask[0] >> subnet_mask[1] >> subnet_mask[2] >> subnet_mask[3] ;
	mask_to_prefix(subnet_mask,&prefix);
	system("cls");
}
void IP_Calculator::set_class() {
	if(Class!='I') return ;
	if(oct[0]>0 && oct[0]<128) Class = 'A';
	if(oct[0]>127 && oct[0]<192) Class = 'B';
	if(oct[0]>191 && oct[0]<224) Class = 'C';
}
void IP_Calculator::set_prefix() {
	prefix = get_prefix_from_class(Class);
}
void IP_Calculator::set_address() {
	int q=prefix;
	for(int i=0; i<4; i++) {
		int k=get_streak(q);
		network_adr[i] = octet_cvt(oct[i],k,0);
		broadcast_address[i] = octet_cvt(oct[i],k,1);
		q-=8;
	}
}
void IP_Calculator::set_netmask() {
	int q=prefix,k;
	for(int i=0; i<4; i++) {
		k=get_streak(q);
		subnet_mask[i]=streak_1_to_dec(k);
		q-=8;
	}
}
bool IP_Calculator::check_error() {
	if (prefix<8 || prefix>30 || Class=='I') return false;
	if (oct[0]>223 || oct[0]==127 || oct[0]==0 || Invalid_IPv4(oct)==false) return false;
	return true;
}
void IP_Calculator::print_data() {
	set_address();
	set_netmask();
	system("cls");
	if(check_error()==false) {
		cout << "Nhap sai du lieu hoac IP khong ho tro !\nCac nguyen nhan:\n - Nhap Class D hoac E (Octet 1 > 223)\n";
		cout << " - Nhap cac IP dac biet: 0.x.x.x hoac 127.x.x.x \n";
		cout << " - Prefix lon hon 30 hoac nho hon 8\n - Khong dung dinh dang IPv4\n\n";
		return ;
	}
	cout << "Dia chi IP: " ;
	print_IP(oct);
	if(isPublic(oct[0],oct[1])) cout << "Public IP\n";
	else cout << "Private IP\n";
	cout << "Class: " << Class << endl;
	cout << "Prefix: " << prefix << endl;
	cout << "NetId = " << prefix << " HostId: = " << 32-prefix << endl;
	cout << "Dia chi mang: ";
	print_IP(network_adr);
	cout << "Dia chi qcao: ";
	print_IP(broadcast_address);
	cout <<"Mat na mang : ";
	print_IP(subnet_mask);
	if(subnet_bits==-1) {
		cout << "\nSo host toi da: " << (long)pow(2,(32-prefix))-2 << " = (2^" << 32-prefix << ")-2\n" ;
		cout << "So dia chi IP: " << (long)pow(2,32-prefix) << " = (2^" << 32-prefix << ")\n" ;
	} else {
		cout << "\nSo luong mang con: " << (long)pow(2,subnet_bits) << " = (2^" << subnet_bits << ")\n";
		cout << "So host / 1 mang con: " << (long)pow(2,32-prefix)-2 << " = (2^" << 32-prefix << ")-2\n";
		cout << "So host toi da cua tat ca cac mang: " << (long)pow(2,subnet_bits)*(long)(pow(2,32-prefix)-2) << endl;
	}
	cout << "\nCac mang nam cung khi:\n" ;
	for(int i=0; i<4; i++) {
		cout << network_adr[i] ;
		if(i!=3) cout << ".";
	}
	cout << " <= x.x.x.x <= ";
	for(int i=0; i<4; i++) {
		cout << broadcast_address[i] ;
		if(i!=3) cout << ".";
	}
	cout << "\n\n";
}
void IP_Calc() {
	system("cls");
	IP_Calculator P1;
	P1.input_ip();
	cout << "Lua chon\n1.Nhap mat na mang\n2.Nhap prefix\n3.Nhap so bit muon them\n4.In du lieu\n";
	int t = getch()-48;
	if(t==1) P1.input_mask();
	if(t==2) P1.input_prefix();
	if(t==3) P1.input_subnet();
	P1.print_data();
}
class Security {
	private:
		bool t=true;
		int tk=1000,days,hours,minutes,seconds;
		int cr_days,cr_hours,cr_minutes,cr_seconds;
		string s_rand;
		bool check_time() {
			if(cr_hours==1 && hours!=1)cr_hours=hours+1;
			int first=totalsecond(hours,minutes,seconds);
			int last=totalsecond(cr_hours,cr_minutes,cr_seconds);
			return (last-first>3600) ? false : true;
		}
		string getrand() {
			gettime(&days,&hours,&minutes,&seconds);
			int res,t,q=minutes*10;
			string s;
			srand (time(0));
			for(int i=0; i<20; i++) {
				int t=((rand()%100)+q*i+hours+seconds)%3;
				res=choose(t);
				res+=((rand()%100)+q+seconds+days)%24+1;
				q=res%5+1;
				s+=(char)res;
			}
			return s;
		}
		bool encode(string s1) {
			string s=s_rand;
			int x,q=s[2];
			int k=(s1[0]-48);
			cout << "k = " << k << endl;
			for(int i=0; i<s.length(); i++) {
				x=((21*k)+(i*i)+(i*9*k)+q*50)%24;
				s[i]=q1(s[i])+x;
				q=s[i]+k;
			}
			s1.erase(0,1);
			cout << "s = " << s << endl << "s1 = " << endl;
			if(s1!=s) return false;
			tk=k*20;
			return true;
		}
		void hashing() {
			string s3;
			s_rand=getrand();
			toClipboard(s_rand);
			cout << "Ma phien : " << s_rand << "\n";
			cout << "Da sao chep ma phien vao bo nho tam\n";
			cout << "Nhap key tuong ung voi ma phien: ";
			getline(cin,s3);
			if(!encode(s3)) t=false;
		}
		void Feature() {
			gettime(&cr_days,&cr_hours,&cr_minutes,&cr_seconds);
/*			if(tk<=0 || t==false || check_time()==false) {
				system("cls");
				if(t==false){
					cout << "\n|----------------------------|\n";
					cout << "| Key da nhap khong hop le ! |\n";
					cout << "|----------------------------|\n";
				}
				else {
					cout <<"\n|-------------------------------------------------------------------------|\n";
					cout <<"| Key het han su dung, vui long khoi dong lai ung dung va nhap key khac ! |\n";
					cout <<"|-------------------------------------------------------------------------|\n";
				}
				getch();
				return ;
			} */
			Choice();
			cout << "Token hien tai: " << tk << endl;
			int t=getch()-48;
			system("cls");
			switch (t) {
				case 1: {
					IP_Calc();
					tk=tk-3;
					break;
				}
				case 2: {
					Calculate_Packet();
					tk=tk-5;
					break;
				}
				case 3: {
					tk=tk-10;
					Throughput_Calculator();
					break;
				}
				case 4: {
					tk=tk-1;
					base_converter();
					break;
				}
				case 5: {
					tk=tk-5;
					fit_mask();
					break;
				}
				case 6: {
					tk=tk-7;
					IPv4_IPv6 ();
					break;
				}
				case 7: {
					valid_port_number();
					break;
				}
				default:
					break;
			}
			cout <<"\n|---------------------------------------------------|\n";
			cout <<"|     Nhan phim bat ky de quay lai trang chu !	    |\n";
			cout <<"|---------------------------------------------------|\n";
			getch();
			Feature();
		}
	public:
		Security() {
			gettime(&days,&hours,&minutes,&seconds);
			hashing();
			Feature();
		}
};
int main() {
	Security P1;
	return 0;
}
