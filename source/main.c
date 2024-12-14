#include <stdio.h>
#include <string.h>
#include <math.h>
#include <3ds.h>

int main() {
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);

	float A = 0, B = 0;
	float z[880];
	char b[880];

	printf("\x1b[2J"); // Clear the screen

	while (aptMainLoop()) {
		memset(b, 32, 880); // Fill with spaces
		memset(z, 0, 3520); // Clear depth buffer

		for (float j = 0; j < 6.28; j += 0.07) {
			for (float i = 0; i < 6.28; i += 0.02) {
				float sini = sin(i);
				float cosi = cos(i);
				float sinj = sin(j);
				float cosj = cos(j);
				float sinA = sin(A);
				float cosA = cos(A);
				float sinB = sin(B);
				float cosB = cos(B);

				float cosj2 = cosj + 2; // Precomputed term
				float mess = 1 / (sini * cosj2 * sinA + sinj * cosA + 5);
				float t = sini * cosj2 * cosA - sinj * sinA;

				// Adjust the constants to shift the donut down by 3 lines
				int x = (int)(30 - 5 + 20 * mess * (cosi * cosj2 * cosB - t * sinB));  // Move left by 5
				int y = (int)(10 - 5.5 + 10 * mess * (cosi * cosj2 * sinB + t * cosB));  // Move up by 3
				y += 3; // Move the donut down by 3 lines
				int o = x + 60 * y;
				int N = (int)(8 * ((sinj * sinA - sini * cosj * cosA) * cosB - sini * cosj * sinA - sinj * cosA - cosi * cosj * sinB));

				if (15 > y && y > 0 && x > 0 && 60 > x && mess > z[o]) {
					z[o] = mess;
					b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
				}
			}
		}

		printf("\x1b[H"); // Reset cursor position

		for (int k = 0; k < 880; k++) {
			putchar(k % 60 ? b[k] : '\n');
		}

		A += 0.04;
		B += 0.02;

		gfxFlushBuffers();
		gfxSwapBuffers();
		gspWaitForVBlank();
	}

	gfxExit();
	return 0;
}
