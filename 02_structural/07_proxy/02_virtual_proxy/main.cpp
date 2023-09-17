#include <iostream>
#include <string>

struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(std::string const& filename) {
        std::cout << "Loading image from " << filename << std::endl;
    }
    void draw() override {
        std::cout << "Drawing image" << std::endl;
    }
};

struct LazyBitmap : Image
{
    LazyBitmap(std::string const& filename) : filename{filename} {}
    ~LazyBitmap() { delete bmp; }

    void draw() override {
        if (!bmp) bmp = new Bitmap(filename);
        bmp->draw();
    }

private:
    Bitmap *bmp{nullptr};
    std::string filename;
};

void draw_image(Image& img)
{
    std::cout << "About to draw the image" << std::endl;
    img.draw();
    std::cout << "Done drawing the image" << std::endl;
}

int main(int argc, char** argv)
{
    Bitmap img{"pokemon.png"};

    LazyBitmap img2{"pokemon.png"};
    draw_image(img2);

    return 0;
}