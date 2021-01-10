#include <string>
#include <fstream>
#include <optional>
#include <iostream>
#include <thread>

#include "../include/View.hpp"
#include "../include/Controller.hpp"
#include "../include/MessageQueues.hpp"
#include "../include/Config.hpp"

using namespace ox;

int main(int argc, char *argv[])
{
    std::ifstream ifs("config.py");
    std::string config_string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    std::optional<Config> o_config = Config::try_from_script(config_string.c_str());
    if (!o_config)
    {
        std::cerr << "Config error!" << std::endl;
        return 1;
    }

    std::shared_ptr<MessageQueues> message_queues = std::make_shared<MessageQueues>();

    auto model = std::make_unique<Controller>(o_config.value(), message_queues);
    std::thread model_thread([&model]() {
        model->run();
    });

    { // w bloku zeby wywolac destruktor view po zakonczeniu view.run()
        View view(o_config.value(), message_queues);
        view.run();
    }

    model_thread.join();
    return 0;
}