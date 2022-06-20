#include "../Headers.h"

int main() 
{
    Server app(8080);

    // return data
    app.Get("/", [&](HttpRequest& request, HttpResponse& response) {
        //----- return html file -----//
        ReadHtml("../template/home.html", response.body);
        //-----------------------------------//

        //----- return json -----//
        JSON o;
        o["status"] = 0;
        o["message"] = "success";
        response.body = o.dump();
        //------------------------------//

        //---- return whatever string ----//
        response.body = "whatever string";
        //--------------------------------//

        //---- custom status -----//
        response.status = HttpStatus::Ok;
        //------------------------//

        //---- custom Headers ------//
        response.AddHeader("key", "value");
        //-------------------------//

        //---- custom Cookie ------//
        response.AddCookie("key", "value");
        //-------------------------//
    });


    // get request data
    app.Get("/custom", [&](HttpRequest& request, HttpResponse& response) {
        //----- get query (if there's no specific query it will return empty string ------//
        std::string q = request.GetQuery("q");
        //----------------------//

        //----- get headers ------//
        std::unordered_map<std::string, std::stirng>& headers = request.GetHeaders();
        //------------------------//
        
        //----- get request body --------//
        std::string body = request.GetBody();
        //-------------------------------//

        //----- get cookie or cookies ------//
        std::string cookie = request.GetCookie("cookie");
        std::unordered_map<std::string, std::string> cookies = request.GetCookies();
        //----------------------------------//
        
    });

    

    // load json body
    app.Post("/post", [&](HttpRequest& request, HttpResponse& response) {
        JSON obj = JSON::Load(request.GetBody());
        std::string account = obj["account"].ToString();
        std::string password = obj["password"].ToString();
        std::string name = obj["name"].ToString();
    });



    app.Run();
    return 0;
}