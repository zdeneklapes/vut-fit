function abs(v) {
    return v < 0 ? -v : v;
}

BEGIN {
    FS=";";
}
{
    LAST_STOCK=$2;
    if ($3 == "sell") {
        STOCK[$2]=STOCK[$2] - $6;
    }
    if ($3 == "buy") {
        STOCK[$2]=STOCK[$2] + $6;
    }
    if ($2 != LAST_STOCK && NR != 1) {
        STOCK[LAST_STOCK]=STOCK[LAST_STOCK];
    }
    PRICES[LAST_STOCK]=$4;
}
END {
    # count price for every stock
    for (stock in STOCK) {
        STOCK_PRICES[stock]=STOCK[stock] * PRICES[stock];
    }
    # initilize MAX and set its value (the biggest stock position)
    # kdyby sirka nebyla nastavena tak 1000
    if ("$WIDTH" == "")
    {
        MAX=1000;
    }
    else {
        for (stock in STOCK_PRICES) {
            if(MAX > (abs(STOCK_PRICES[stock])/"$WIDTH")) {
                continue;
            } else {
                MAX=abs(STOCK_PRICES[stock])/"$WIDTH";
            }
        }
    }
    # print stock graph
    for (stock in STOCK_PRICES)
    {
        COUNT=int(STOCK_PRICES[stock]/MAX);
        #print COUNT;

        if (COUNT >= 0)
        {
            printf("%-10s :", stock);
			if (COUNT != 0)
			{
				printf(" ");
				for(i=0; i < COUNT; i++)
					printf("%c", "#");
			}
            printf("\n");
        }
        else
        {
            printf("%-10s :", stock);
#            abs musi byt jinak nejede
			if (COUNT != 0)
			{
				printf(" ");
				for(i=0; i < abs(COUNT); i++)
					printf("%c", "!");
			}
            printf("\n");
        }
    }
}