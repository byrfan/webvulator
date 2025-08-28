#define WEBVIEW_IMPLEMENTATION
#include "webview.h"
#include "ExpressionParser.hpp"
#include <iostream>

int main() {
    webview::webview w(true, nullptr);
    w.set_title("Calculator");
    w.set_size(480, 320, WEBVIEW_HINT_NONE);

    // Bind a C++ function callable from JS
    w.bind("addNumbers", [](std::string args) -> std::string {
        // args is a JSON array string: "[a, b]"
        double a, b;
        sscanf(args.c_str(), "[%lf,%lf]", &a, &b);
        double result = a + b;
        std::cout << "Sum: " << result << "\n";
        return std::to_string(result);
    });

    // HTML with JS calling the bound function
    w.set_html(R"(
        <html>
        <body>
            <h1>Calculator</h1>
            <input id='a' type='number' value='1'>
            <input id='b' type='number' value='2'>
            <button onclick='doAdd()'>Add</button>
            <script>
            async function doAdd() {
                let a = parseFloat(document.getElementById('a').value);
                let b = parseFloat(document.getElementById('b').value);
                let result = await addNumbers(a, b);
                alert('Result: ' + result);
            }
            </script>
        </body>
        </html>
    )");

    w.run();
}

