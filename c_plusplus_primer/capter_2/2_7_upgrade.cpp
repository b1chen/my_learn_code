#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <functional>
#include <algorithm>
#define RESET "\033[0m"
#define BLACK "\033[30m" /* Black */
#define RED "\033[31m" /* Red */
#define GREEN "\033[32m" /* Green */

class Parse_ini{
public:
	Parse_ini(std::string filename):filename(filename){
		fin.open(filename.c_str());
		if (fin.fail()){
			std::cout << "open file "<< filename << " fail." << std::endl;
		}
	}
	~Parse_ini(){
		if (fin.is_open()){
			fin.close();
		}
	}
	
	bool do_parse(){
		parse_lines_to_item();
		return true;
	}
	
	void print_items(){
		std::cout << RED << __func__ << RESET << std::endl;
		std::map<std::string, std::vector<std::string> >::iterator iter = items.begin();
		while(iter != items.end()){
			std::cout << GREEN << iter->first << RESET << std::endl;
			std::vector<std::string>::iterator s_iter = iter->second.begin();
			for(; s_iter != iter->second.end(); s_iter++){
				std::cout << *s_iter << std::endl;
			}
			iter++;
		}
	}
private:
	void parse_lines_to_item();
	std::string line_delete_annotation(std::string);
	std::string erase_space_before_start_after_end(std::string);
	bool is_itemname_line(std::string line);
	std::string get_item_name(std::string line);
	std::string filename;
	std::ifstream fin;
	std::map<std::string, std::vector<std::string> > items;
};

std::string Parse_ini::line_delete_annotation(std::string line){
	//find(line.begin(), line.end(), '#');
	line.erase(std::find(line.begin(), line.end(), '#'), line.end());
	return line;
}

std::string Parse_ini::erase_space_before_start_after_end(std::string line){
	line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
	line.erase(find_if(line.rbegin(), line.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), line.end());
	return line;
}

bool Parse_ini::is_itemname_line(std::string line){
	if ( (line[0] == '[') && (line[line.length() - 1] == ']') ){
		return true;
	}
	return false;
}

std::string Parse_ini::get_item_name(std::string line){
	line.erase(line.begin());
	line.erase(line.end() - 1);
	return line;
}

void Parse_ini::parse_lines_to_item(){
	std::string line_content;
	std::string cur_item_name;
	while(fin){
		getline(fin, line_content);
		line_content = erase_space_before_start_after_end(line_content);
		line_content = line_delete_annotation(line_content);
		if (line_content.empty()) continue;
		if (is_itemname_line(line_content)){
			cur_item_name = get_item_name(line_content);
			items.insert(make_pair(cur_item_name, std::vector<std::string>()));
		}else{
			items[cur_item_name].push_back(line_content);
		}
	}
}
//能不能拷贝?
int main(){
	Parse_ini parse_ini("configure.ini");
	parse_ini.do_parse();
	parse_ini.print_items();
}
