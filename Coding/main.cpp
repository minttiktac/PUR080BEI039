#include "error.hpp"
#include "renderWindow.hpp"
#include "login.hpp"

int main()
{
    bool isLoggedIn = true;
    
    if (isLoggedIn)
    {
        return render_window();
        return 0;
    }
    else 
    {
        return login();
        return 0;
    }
    return 0;
}



