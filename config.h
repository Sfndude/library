/************************
 * Config c("berkas");
 * 
 * c.key("info");
 * c.write("nama","shofuwan");
 * 
 * std::cout<<c.read("nama");<<std::endl
 * std::cout<<c.exist("nama")<<std::endl;
 * c.purge("name");
 ************************/

/************************
 * info.nama=shofuwan
 * --------STEP----------
 * ~deleted object~
 ************************/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

class Config{
private:
    std::string key_name="", cfg_name="", obj_name="";
    inline void cpfile(void);
    inline void cpfile_(void);
    inline void replace_(std::string t_old, std::string t_new);
    inline void sort(void);
    inline int line_total(void);
    inline std::string fget_data(std::string data,int index);
public:
    Config(std::string cfg){
        cfg_name=cfg;
        std::ifstream r((cfg_name+".cfg").c_str());
        if(!r.good()){
            std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
            w<<"#CONFIG#FILE\n";
            w.close();
        }
        r.close();
    }
    inline void key(std::string key);
    inline std::string get_key(void);
    inline void object(std::string obj);
    inline std::string read(std::string obj, int index);
    inline std::string read(std::string obj);
    inline int readInt(std::string obj, int index);
    inline int readInt(std::string obj);
    inline float readFloat(std::string obj, int index);
    inline float readFloat(std::string obj);
    inline int write(std::string obj, std::string val);
    inline int write(std::string obj, int val);
    inline int write(std::string obj, float val);
    inline int write(std::string val);
    inline int write(int val);
    inline int write(float val);
    inline int exist(std::string txt);
    inline int purge(std::string obj);
    inline int valueTotal(std::string obj);
    inline std::string get_config(void);
};
/*--------------PRIVATE---------------*/
inline void Config::cpfile(void){
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg.backup").c_str());
    std::string temp;
    while(r>>temp)
        w<<temp<<"\n";
    w.close();
    r.close();
}
inline void Config::cpfile_(void){
    std::ifstream r((cfg_name+".cfg.backup").c_str());
    std::ofstream w((cfg_name+".cfg").c_str());
    std::string temp;
    while(r>>temp)
        w<<temp<<"\n";
    w.close();
    r.close();
}
inline void Config::replace_(std::string t_old, std::string t_new){
    cpfile();
    std::ofstream w((cfg_name+".cfg").c_str());
    std::ifstream r((cfg_name+".cfg.backup").c_str());
    std::string temp;

    while(r>>temp){
        if(temp==t_old)
            temp=t_new;
        w<<temp<<"\n";
    }
    r.close();
    w.close();
    cpfile();
    cpfile_();
}
inline void Config::sort(void){
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg.backup").c_str());
    std::string temp;
    std::vector<std::string> data;
    int count=0;

    while(r>>temp)
        if(temp!="#CONFIG#FILE")
            data.push_back(temp);
        std::sort(data.begin(),data.end());
    w<<"#CONFIG#FILE\n";
    for(int x=0;x<line_total();x++)
        w<<data[x]<<"\n";
    r.close();
    w.close();
    cpfile_();
    remove((cfg_name+".cfg.backup").c_str());
}
inline int Config::line_total(void){
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;
    int line=0;

    while(r>>temp)
        if(temp!="#CONFIG#FILE")
            line++;
    return line;
}
inline std::string Config::fget_data(std::string data, int index){
    std::vector<std::string> ret;
    std::string temp;
    data+="*";
    for(int cp=0;cp<data.length();cp++){
        if(data[cp]==','||cp==(data.length()-1)){
            ret.push_back(temp);
            temp="";
        }else
            temp+=data[cp];
    }
    return ret[index];
}
/*--------------PUBLIC----------------*/
/*inline Config::Config(std::string cfg){
    cfg_name=cfg;
    std::ifstream r((cfg_name+".cfg").c_str());
    if(!r.good()){
        std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
        w<<"#CONFIG#FILE\n";
        w.close();
    }
    r.close();
}*/
inline void Config::key(std::string key){key_name=key;}
inline std::string Config::get_key(void){return key_name;}
inline void Config::object(std::string obj){obj_name=obj;}
inline int Config::write(std::string obj, std::string val){
    if(key_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        sort();
        replace_(temp,(key_name+"."+obj+"="+val).c_str());
        return 1;
    }else{
        sort();
        w<<key_name<<"."<<obj<<"="<<val<<"\n";
        return 0;
    }

    r.close();
    w.close();
}
inline int Config::write(std::string obj, int val){
    if(key_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        replace_(temp,(key_name+"."+obj+"="+std::to_string(val)).c_str());
        sort();
        return 1;
    }else{
        w<<key_name<<"."<<obj<<"="<<val<<"\n";
        sort();
        return 0;
    }

    r.close();
    w.close();
}
inline int Config::write(std::string obj, float val){
    if(key_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        replace_(temp,(key_name+"."+obj+"="+std::to_string(val)).c_str());
        sort();
        return 1;
    }else{
        w<<key_name<<"."<<obj<<"="<<val<<"\n";
        sort();
        return 0;
    }

    r.close();
    w.close();
}
inline int Config::write(std::string val){
    if(key_name.empty() && obj_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj_name+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        replace_(temp,(key_name+"."+obj_name+"="+val).c_str());
        sort();
        return 1;
    }else{
        w<<key_name<<"."<<obj_name<<"="<<val<<"\n";
        sort();
        return 0;
    }

    r.close();
    w.close();
}
inline int Config::write(int val){
    if(key_name.empty() && obj_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj_name+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        replace_(temp,(key_name+"."+obj_name+"="+std::to_string(val)).c_str());
        sort();
        return 1;
    }else{
        w<<key_name<<"."<<obj_name<<"="<<val<<"\n";
        sort();
        return 0;
    }

    r.close();
    w.close();
}
inline int Config::write(float val){
    if(key_name.empty() && obj_name.empty())
        return -1;
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj_name+"=").c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0){
        replace_(temp,(key_name+"."+obj_name+"="+std::to_string(val)).c_str());
        sort();
        return 1;
    }else{
        w<<key_name<<"."<<obj_name<<"="<<val<<"\n";
        sort();
        return 0;
    }

    r.close();
    w.close();
}
inline std::string Config::read(std::string obj, int index){
    if(key_name.empty())
        return "-1";
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find(std::string(key_name+"."+obj+"="))!=std::string::npos)
            break;
    if(!(temp.find(key_name)==std::string::npos))
        return fget_data(temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,""),index);
    else
        return "-1";
    r.close();
}
inline std::string Config::read(std::string obj){
    if(key_name.empty())
        return "-1";
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find(std::string(key_name+"."+obj+"="))!=std::string::npos)
        //if(temp==(std::string(key_name+"."+obj+"=")+std::string(temp).substr((key_name.length()+obj.length())+2,temp.length()-(key_name.length()+obj.length())+2)))
            break;
    if(!(temp.find(key_name)==std::string::npos))
        return temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,"");
    else
        return "-1";
    r.close();
}
inline int Config::readInt(std::string obj, int index){
    if(key_name.empty())
        return -1;
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find(std::string(key_name+"."+obj+"="))!=std::string::npos)
            break;
    if(!(temp.find(key_name)==std::string::npos))
        return atoi(fget_data(temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,""),index).c_str());
    else
        return -1;
    r.close();
}
inline int Config::readInt(std::string obj){
    if(key_name.empty())
        return -1;
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find((key_name+"."+obj+"=").c_str())!=std::string::npos)
            break;
    
    if(!(temp.find(key_name)==std::string::npos))
        return atoi(temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,"").c_str());
    else
        return -1;
}
inline float Config::readFloat(std::string obj, int index){
    if(key_name.empty())
        return -1;
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find(std::string(key_name+"."+obj+"="))!=std::string::npos)
            break;
    if(!(temp.find(key_name)==std::string::npos))
        return atof(fget_data(temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,""),index).c_str());
    else
        return -1;
    r.close();
}
inline float Config::readFloat(std::string obj){
    if(key_name.empty())
        return -1;
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;

    while(r>>temp)
        if(temp.find((key_name+"."+obj+"=").c_str())!=std::string::npos)
            break;
    
    if(!(temp.find(key_name)==std::string::npos))
        return atof(temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,"").c_str());
    else
        return -1;
}
/**********************************
 * return 0 = data doesn't exist
 * return -1 = data exist as key
 * return 1 = data exist as object
 * return 2 = data exist as value
 **********************************/
inline int Config::exist(std::string txt){
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;
    int ret=0;

    while(r>>temp){
        if(temp.find((txt+".").c_str())!=std::string::npos){
            ret=(-1);
            break;
        }else if(temp.find(("."+txt).c_str())!=std::string::npos){
            ret=1;
            break;
        }else if(temp.find(("="+txt).c_str())!=std::string::npos){
            ret=2;
            break;
        }
    }

    r.close();
    return ret;
}
inline int Config::purge(std::string obj){
    std::ifstream r((cfg_name+".cfg").c_str());
    std::ofstream w((cfg_name+".cfg").c_str(),std::ios::app);
    std::string temp;
    bool stat=0;

    while(r>>temp){
        if(temp.find((key_name+"."+obj).c_str())!=std::string::npos){
            stat=1;
            break;
        }
    }
    if(stat!=0)
        replace_(temp,"\0");

    r.close();
    w.close();
    if(stat!=0)
        return 0;
    else
        return -1;
}
inline int Config::valueTotal(std::string obj){
    if(key_name.empty())
        return -1;
    sort();
    std::ifstream r((cfg_name+".cfg").c_str());
    std::string temp;
    int total=0;

    while(r>>temp)
        if(temp.find(std::string(key_name+"."+obj+"="))!=std::string::npos)
            break;
    if(!(temp.find(key_name)==std::string::npos))
        temp=temp.replace(temp.begin(),temp.begin()+(key_name.length()+obj.length())+2,"");
    for(int cp=0;cp<temp.length();cp++)
        if(temp[cp]==',')
            total++;
    total+=1;

    r.close();
    return total; 
}
inline std::string Config::get_config(void){return cfg_name;}