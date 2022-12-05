#include <iostream>
#include <JsonConfiger/Config/ConfigManager.h>

#include "JsonConfiger/Archive/JsonArchive.h"
#include "JsonConfiger/Config/IJsonConfig.h"

int main(int argc, char** argv)
{
    std::string configFolder = "Configs";

    JC::ConfigManager manager(configFolder);

    class Config: public JC::IJsonConfig
    {
    public:
        Config(): IJsonConfig("Config.json")
        {
        }
        
        void Serialize(JC::JsonArchive* stream) override
        {
            stream->Serialize("val", val);
        }
        
        bool Equals(const IJsonConfig* oth) const override
        {
            auto casted = dynamic_cast<const Config*>(oth);
            assert(casted);
            return casted->val == val;
        }
        int val = 0;
    };
    JC::ConfigMetadata data = manager.CreateConfig<Config>();
    
    return 0;
}
