#define WEBVIEW_IMPLEMENTATION
#include <iostream>
#include "ExpressionParser.hpp"
#include "webview.h"
#include "fio.hpp"

int main()
{
    webview::webview w(true, nullptr);
    w.set_title("Calculator");
    w.set_size(480, 720, WEBVIEW_HINT_MIN);
    
    w.set_html(readFile("index.html"));

    w.run();
    return 0;
}
