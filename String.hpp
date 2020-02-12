/*
	Yazar 		:	Arif ALTIOK
	
	Tarih		: 	11/02/2020
	
	Amac		:	string islemleri kapsuluze etme
					Ornegin -> split,combine, trim vb ...
	
	Aciklamalar 	: 	Bazi islemlerde vector veri yapisi kullanir
					Istenirse typedef SplitContainer degistirilebilir
					
	Kullanim 	: 	Prototiplerde bahsedildi.

*/

#ifndef STRING_HPP
#define STRING_HPP
#include <iostream>
#include <sstream>
#include <vector>

class String{
	std::string data;
	public:
		
		typedef std::vector<String> SplitContainer;
		typedef SplitContainer::iterator Iterator;
		
		String(const std::string& data = "");
		
		template<typename T>
		String(const T& data);
		// Atama operatorundeki sartlar gecerli
		
		template<typename T>
		String& operator=(const T& data);
		 // tüm parametre tiplerini kabul eder.
		 // Ancak gonderilen parametre sýnýfýnýn operator << yuklu olmasý gerekir
		
		std::string getContent()const;
		// icerigi std::string olarak doner
		
		template<typename T>
		SplitContainer split(const T& delimiter)const;
		// atama operatorundeki sartlar gecerli ve alttaki splite cagri yapar.
		
		SplitContainer split(const String& delimiter)const;
		//Belirtilen delimitera gore tum nesneyi bolerek vector halinde doner.
		// delimiter elde edilen boluntulere dahil olmaz.
		

		String combine(SplitContainer& container);
		//Vector halinde verilen String nesnelerinin arasilarina icerigini yerlestirir.
		
		
		
		String rtrim(const char *tokens = " \r\n\t\v\f");
		String ltrim(const char* tokens = " \r\n\t\v\f");
		String trim(const char* tokens = " \r\n\t\v\f");
		// trim methodlarý tokens halinde char parametreleri sol,sag ve ikiyon olarak temizler.
		
		// okuma yazma islemleri (dosyalar ve akýs nesneleri icin kolaylik)
		friend String& operator>>(std::istream& in,String& obj);	
		friend std::ostream& operator<<(std::ostream& out,const String& obj);
};

String::String(const std::string& data)
: data(data)
{	}

template<typename T>
String::String(const T& data){
	*this = data;
}

template<typename T>
String& String::operator=(const T& data){
	std::stringstream ss;
	ss << data;
	getline(ss,this->data);
	return *this;
}

std::string String::getContent()const{	return data;	}

template<typename T>
String::SplitContainer String::split(const T& delimiter)const{
	String delim = delimiter;
	return split(delim);
}

String::SplitContainer String::split(const String& delimiter)const{
	SplitContainer retval;
	std::size_t first = 0;
	std::size_t second;
	std::size_t size = delimiter.data.length();
	String str;
	while((second = data.find(delimiter.data,first)) != std::string::npos){
		str = data.substr(first,second - first);
		retval.push_back(str);
		first = second + size;
	}
	
	if(first <= data.length()){
		str = data.substr(first);
		retval.push_back(str);
	}	
	return retval;
}


String String::combine(SplitContainer& container){
	String retval;
	if(!container.empty()){
		Iterator iter = container.begin();
		retval = *iter;
		while(++iter != container.end())
			retval.data += data + iter->data;
	}
	return retval;
}

String String::rtrim(const char *tokens){
	std::size_t index = data.find_last_not_of(tokens);
	return String(index == std::string::npos ? "" : data.substr(0,index + 1));
}

String String::ltrim(const char* tokens){
	std::size_t index = data.find_first_not_of(tokens);
	return String(index == std::string::npos ? "" : data.substr(index));
}

String String::trim(const char* tokens){
	return ltrim(tokens).rtrim(tokens);
}

String& operator>>(std::istream& in,String& obj){
	std::string line;
	in >> line;
	obj.data += line + " ";
	return obj;
}
	
std::ostream& operator<<(std::ostream& out,const String& obj){
	out << obj.data;
	return out;
}

#endif



