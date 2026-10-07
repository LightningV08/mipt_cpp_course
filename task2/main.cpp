#include <algorithm>
#include <functional>
#include <iostream>
#include <string>

using TextTransform = std::function<std::string(std::string)>;

class TextProcessor {
public:
    explicit TextProcessor(TextTransform strategy) : strategy_(strategy) {}

    void set_strategy(TextTransform strategy) {
        strategy_ = strategy;
    }

    std::string process(std::string text) const {
        return strategy_(text);
    }

private:
    TextTransform strategy_;
};


int main() {
    TextTransform unchanged = [](std::string text) { return text; };
    TextTransform reversed = [](std::string text) {
        std::reverse(text.begin(), text.end());
        return text;
    };

    TextProcessor processor(unchanged);
    std::cout << processor.process("abc") << '\n';

    processor.set_strategy(reversed);
    std::cout << processor.process("abc") << '\n';

    return 0;
}
