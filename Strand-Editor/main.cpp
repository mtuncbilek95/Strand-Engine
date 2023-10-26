#include <cstdio>

// For test purposes
class EDITOR_API Editor
{
public:
    FORCEINLINE Editor()
    {
        printf("Editor created!\n");
    }
};

int main()
{
    Editor editor;
    return 0;
}