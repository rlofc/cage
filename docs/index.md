#<cldoc:index>

Cage ( Ain't a Game Engine )

![alt text](images/cage.png)
# Cage Ain't a Game Engine
Cage is an educational game development library. 
It is designed and developed to help me teach 2D game dev using the C programming language.
Cage prefers readability and simplicity, in the spirit of
**less is more**.

Cage is minimal and has a naive design so people with almost no 
game or graphics development experience can jump right in. Internally, 
Cage contains and restraints SDL2, the Simple Direct-media Library.
However, apart of knowing it is in there you will not have
to deal with SDL directly.

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

For a more complete example, take a look here:
[http://rlofc.github.io/cage/samples/wizard/doc/src/wizard.html](http://rlofc.github.io/cage/samples/wizard/doc/src/wizard.html)

