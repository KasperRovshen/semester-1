проверено - E

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "bmph.h"


int calculateNewSize(BMPHeader header) {
        int rowSize = header.width * 3;
        int paddedRowSize = rowSize;
        if (rowSize % 4 != 0) {
        paddedRowSize += 4 - (rowSize % 4); 
    }
    return paddedRowSize;
}


BMP readbmp(std::string filename) {
    BMP image;
    setlocale(LC_ALL, "Rus"); 

    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Не удается открыть BMP-файл для чтения." << std::endl;
        throw std::runtime_error("Не удается открыть BMP-файл для чтения.");
    }

    inputFile.read(reinterpret_cast<char*>(&image.header), sizeof(BMPHeader));

    int sizeRow = calculateNewSize(image.header);
    int sizePadded = sizeRow * image.header.height;

    image.pixels = new unsigned char[sizePadded];
    inputFile.read(reinterpret_cast<char*>(image.pixels), sizePadded);

    inputFile.close();
    return image;
}

void writebmp(std::string filename, BMP image) {
    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile) {
        throw std::runtime_error("Unable to create the BMP file for writing.");
    }

    int rowSize = calculateNewSize(image.header);

    outputFile.write(reinterpret_cast<char*>(&image.header), sizeof(BMPHeader));

    int bytesToWrite = image.header.dataOffset - sizeof(BMPHeader);
    for (int i = 0; i < bytesToWrite; i++) {
        char extraByte = 0;
        outputFile.write(&extraByte, 1);
    }

    for (int y = 0; y < image.header.height; y++) {
        int pixelOffset = y * rowSize;
        outputFile.write(reinterpret_cast<char*>(image.pixels + pixelOffset), rowSize);
    }

    outputFile.close();
}


BMP rotateRight(BMP image) {
    BMP newImage;

    int bpp = image.header.bitsPerPixel / 8;

    newImage.header = image.header;
    std::swap(newImage.header.width, newImage.header.height);

    int newRowSize = ((newImage.header.width * bpp + 3) / 4) * 4;
    int oldRowSize = calculateNewSize(image.header);

    newImage.header.fileSize = sizeof(BMPHeader) + newRowSize * newImage.header.height;
    newImage.header.dataSize = newRowSize * newImage.header.height;
    newImage.pixels = new unsigned char[newImage.header.dataSize];

    for (int x = 0; x < newImage.header.height; x++) {
        for (int y = 0; y < newImage.header.width; y++) {
            int oldOffset = y * oldRowSize + x * bpp; 
            int newOffset = (newImage.header.height - 1 - x) * newRowSize + y * bpp;
    
            for (int channel = 0; channel < bpp; channel++) {
                newImage.pixels[newOffset + channel] = image.pixels[oldOffset + channel];
            }
        }
    }

    return newImage;
}


BMP rotateLeft(BMP image) {
    BMP newImage;

    int bpp = image.header.bitsPerPixel / 8; 

    newImage.header = image.header;
    std::swap(newImage.header.width, newImage.header.height);

    int newRowSize = ((newImage.header.width * bpp + 3) / 4) * 4;
    int oldRowSize = calculateNewSize(image.header);

    newImage.header.fileSize = sizeof(BMPHeader) + newRowSize * newImage.header.height;
    newImage.header.dataSize = newRowSize * newImage.header.height;

    newImage.pixels = new unsigned char[newImage.header.dataSize];

    for (int x = 0; x < newImage.header.height; x++) {
        for (int y = 0; y < newImage.header.width; y++) {
            int oldOffset = y * oldRowSize + x * bpp;
            int newOffset = x * newRowSize + (newImage.header.width - 1 - y) * bpp;

            for (int channel = 0; channel < bpp; channel++) {
                newImage.pixels[newOffset + channel] = image.pixels[oldOffset + channel];
            }
        }
    }

    return newImage;
}

// Функция для вычисления ядра фильтра Гаусса
double* calculateGaussianKernel(double sigma, int kernelSize) {
    double* kernel = new double[kernelSize];
    
    for (int i = 0; i < kernelSize; i++) {
        double x = i - (kernelSize - 1) / 2;
        double value = std::exp(-(x * x) / (2 * sigma * sigma));
        kernel[i] = value;
    }

    double sum = 0.0;
    for (int i = 0; i < kernelSize; i++) {
        sum += kernel[i];
    }

    for (int i = 0; i < kernelSize; i++) {
        kernel[i] /= sum;
    }

    return kernel;
}

// Функция для применения фильтра Гаусса к пикселям изображения
void applyGaussianFilterToPixels(BMP& image, double* kernel, int kernelSize) {
    int bpp = image.header.bitsPerPixel / 8;
    int rowSize = ((image.header.width * bpp + 3) / 4) * 4;

    BMP blurredImage = image;

    for (int y = 0; y < image.header.height; y++) {
        for (int x = 0; x < image.header.width; x++) {
            std::vector<double> colorChannels(bpp, 0.0);

            for (int i = 0; i < kernelSize; i++) {
                int posX = x + i - (kernelSize - 1) / 2;
                if (posX < 0) posX = 0;
                if (posX >= image.header.width) posX = image.header.width - 1;

                int pixelOffset = y * rowSize + posX * bpp;

                for (int channel = 0; channel < bpp; channel++) {
                    colorChannels[channel] +=
                        (double)(image.pixels[pixelOffset + channel]) * kernel[i];
                }
            }

            int pixelOffset = y * rowSize + x * bpp;
            for (int channel = 0; channel < bpp; channel++) {
                blurredImage.pixels[pixelOffset + channel] =
                    (unsigned char)(colorChannels[channel]);
            }
        }
    }

    image = blurredImage;
}

// Основная функция для применения фильтра Гаусса
void applyFilterGaussian(BMP& image, double sigma) {
    int kernelSize = (6 * sigma) + 1;
    double* kernel = calculateGaussianKernel(sigma, kernelSize);

    applyGaussianFilterToPixels(image, kernel, kernelSize);

    delete[] kernel;
}


int main() {
    setlocale(LC_ALL, "Rus");
    try {
        BMP image = readbmp("29019073_7392521 (1).bmp");

        BMP rotatedImageRight = rotateRight(image);
        writebmp("rotatedRight.bmp", rotatedImageRight);
        std::cout << "Изображение повернуто на 90 градусов и сохранено как rotatedrightAirplane.bmp" << std::endl;

        BMP rotatedImageLeft = rotateLeft(image);
        writebmp("rotatedleft.bmp", rotatedImageLeft);
        std::cout << "Изображение повернуто на 90 градусов и сохранено как rotatedleftAirplane.bmp" << std::endl;

        double sigma;
        std::cout << "sigma: ";
        std::cin >> sigma;
        applyFilterGaussian(image, sigma);
        writebmp("filter.bmp", image);
        std::cout << "Размытие по Гауссу применено и сохранено как filter.bmp." << std::endl;

        
        delete[] rotatedImageRight.pixels;
        delete[] rotatedImageLeft.pixels;
        delete[] image.pixels;


    } 
    
    catch (std::exception const& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
