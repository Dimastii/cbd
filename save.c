/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cveeta <cveeta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 11:04:08 by cveeta            #+#    #+#             */
/*   Updated: 2021/02/17 16:20:38 by cveeta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "cub.h"

const int BYTES_PER_PIXEL = 3; /// red, green, & blue
const int FILE_HEADER_SIZE = 14;
const int INFO_HEADER_SIZE = 40;



int screen(t_vars *vars)
{
	int height = vars->size_win_h;
	int width = vars->size_win_w;
	unsigned char image[height][width][BYTES_PER_PIXEL];
	char* imageFileName = (char*) "bitmapImage.bmp";
	t_rgb clr;
	clr.clr = 0;
	clr.r = 0;
	clr.g = 0;
	clr.b = 0;
	printf("%p\n", vars->img);
	int i, j;
	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			clr.clr = my_mlx_pixel_take(vars->img, i, j);
			int_to_rgb(&clr, clr.clr);
			clr.clr = 0;
			image[i][j][2] = (unsigned char) (clr.r);           ///red
			image[i][j][1] = (unsigned char) (clr.g);           ///green
			image[i][j][0] = (unsigned char) (clr.b);			///blue
		}
	}

	generateBitmapImage((unsigned char*) image, height, width, imageFileName);
	printf("Image generated!!");
}

void generateBitmapImage (unsigned char* image, int height, int width, char* imageFileName)
{
	int widthInBytes = width * BYTES_PER_PIXEL;

	unsigned char padding[3] = {0, 0, 0};
	int paddingSize = (4 - (widthInBytes) % 4) % 4;

	int stride = (widthInBytes) + paddingSize;
	int fd = open(imageFileName, O_CREAT | (O_WRONLY));
	printf("fd = %d ",fd);
	unsigned char* fileHeader = createBitmapFileHeader(height, stride);
	write(fd, fileHeader, FILE_HEADER_SIZE);
	unsigned char* infoHeader = createBitmapInfoHeader(height, width);
	write(fd, infoHeader, INFO_HEADER_SIZE);
	int i;
	for (i = 0; i < height; i++)
	{
		write(fd, (image + (i*widthInBytes)), BYTES_PER_PIXEL * width);
		write(fd, &padding, paddingSize);
	}
	close(fd);
}

unsigned char* createBitmapFileHeader (int height, int stride)
{
	int fileSize = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);

	static unsigned char fileHeader[] = {
			0,0,     /// signature
			0,0,0,0, /// image file size in bytes
			0,0,0,0, /// reserved
			0,0,0,0, /// start of pixel array
	};

	fileHeader[ 0] = (unsigned char)('B');
	fileHeader[ 1] = (unsigned char)('M');
	fileHeader[ 2] = (unsigned char)(fileSize      );
	fileHeader[ 3] = (unsigned char)(fileSize >>  8);
	fileHeader[ 4] = (unsigned char)(fileSize >> 16);
	fileHeader[ 5] = (unsigned char)(fileSize >> 24);
	fileHeader[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

	return fileHeader;
}

unsigned char* createBitmapInfoHeader (int height, int width)
{
	static unsigned char infoHeader[] = {
			0,0,0,0, /// header size
			0,0,0,0, /// image width
			0,0,0,0, /// image height
			0,0,     /// number of color planes
			0,0,     /// bits per pixel
			0,0,0,0, /// compression
			0,0,0,0, /// image size
			0,0,0,0, /// horizontal resolution
			0,0,0,0, /// vertical resolution
			0,0,0,0, /// colors in color table
			0,0,0,0, /// important color count
	};

	infoHeader[ 0] = (unsigned char)(INFO_HEADER_SIZE);
	infoHeader[ 4] = (unsigned char)(width      );
	infoHeader[ 5] = (unsigned char)(width >>  8);
	infoHeader[ 6] = (unsigned char)(width >> 16);
	infoHeader[ 7] = (unsigned char)(width >> 24);
	infoHeader[ 8] = (unsigned char)(height      );
	infoHeader[ 9] = (unsigned char)(height >>  8);
	infoHeader[10] = (unsigned char)(height >> 16);
	infoHeader[11] = (unsigned char)(height >> 24);
	infoHeader[12] = (unsigned char)(1);
	infoHeader[14] = (unsigned char)(BYTES_PER_PIXEL*8);

	return infoHeader;
}
