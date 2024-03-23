#include <stdio.h>

int main()
{
    double input;
    printf("ml' nob:\n");
    int result = scanf("%lf", &input);

    if (result == 1)
    {
        int intPart = (int)input;

        if (intPart == input)
        {
            if (intPart >= 0 && intPart <= 8)
            {
                printf("Qapla'\n");
                if (intPart == 0)
                {
                    printf("noH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
                }
                if (intPart == 1)
                {
                    printf("bortaS bIr jablu'DI' reH QaQqu' nay'.\n");
                }
                if (intPart == 2)
                {
                    printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
                }
                if (intPart == 3)
                {
                    printf("bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
                }
                if (intPart == 4)
                {
                    printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
                }
                if (intPart == 5)
                {
                    printf("Suvlu'taHvIS yapbe' HoS neH.\n");
                }
                if (intPart == 6)
                {
                    printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
                }
                if (intPart == 7)
                {
                    printf("Heghlu'meH QaQ jajvam.\n");
                }
                if (intPart == 8)
                {
                    printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
                }
            }
            else if (intPart < 0 || intPart > 8)
            {
                printf("Qih mi' %d\n", intPart);
            }
        }
        else
        {
            printf("bIjatlh 'e' yImev\n");
        }
    }
    else
    {
        printf("Neh mi'\n");
    }
    return 0;
}