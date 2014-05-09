#<cldoc:index>

Cage ( Ain't a Game Engine )

![alt text](cage.png)
# Cage Ain't a Game Engine
Cage is an educational game development library. 
It is designed and developed to help the absolute newcommer write 2D games using the C programming language.
Cage prefers readability and simplicity, in the spirit of
**less is more**.

Cage is minimalistic and has a naive design so people with no 
game or graphics development experience can jump right in. Internally, 
Cage contains and restraints SDL, the Simple Direct-media Library.
However, apart of knowing it is in there, you will not have
to deal with SDL directly.

If you are a beginner, who just wants to try writing real 2D games using C, then
Cage is for you. 


```c
int prepare( struct toolbox* tb )
{
    tb->drawer = create_font( tb->screen, "font.png" );
    return ( tb->drawer ? 0 : -1 );
}

void update( struct toolbox* tb )
{
    draw_text( tb->screen, tb->drawer, "Hello, World", xy( 0, 0 ) );
}

void teardown( struct toolbox* tb )
{
    destroy_font( tb->drawer );
}

int main(int argc, char ** argv)
{
    struct gamestate hello_world = { prepare, update, teardown };
    return gameloop( &hello_world );
}
```
