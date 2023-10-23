#include <cstdio>

// For test purposes
class EDITOR_API Editor
{
public:
    FORCEINLINE Editor() { printf("Editor\n"); }
};

int main()
{
    Editor editor;
    return 0;
}