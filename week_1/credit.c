#include <cs50.h>
#include <stdio.h>

int get_cc_len(long cc)
{
	int len;

	len = 0;
	while (cc > 0)
	{
		cc /= 10;
		len++;
	}
	return (len);
}

int check_cc_len(int len)
{
	if (len != 13 && len != 15 && len != 16)
	{
		printf("INVALID\n");
		return (0);
	}
}

int check_sum(long cc)
{
	int d1;
	int d2;
	int mod1;
	int mod2;
	int sum1;
	int sum2;

	sum1 = 0;
	sum2 = 0;
	while (cc > 0)
	{
		// Remove last digit and add to sum1
		mod1 = cc % 10;
		cc /= 10;
		sum1 += mod1;

		// Remove second last digit
		mod2 =  cc % 10;
		cc /= 10;

		// Double second last digit and add digits to sum2
		mod2 *=  2;
		d1 = mod2 % 10;
		d2 = mod2 / 10;
		sum2 += d1 + d2;
	}
	return (sum1 + sum2);
}

int get_start_digits(long cc)
{
	while (cc > 100)
		cc /= 10;
	return (cc);
}

int main(void)
{
	int	 len;
	int	 total;
	int	 start_digits;
	long	credit_card;

	credit_card = get_long("Number: ");
	len = get_cc_len(credit_card);
	if (!check_cc_len(len))
		return (0);
	else
	{
		total = check_sum(credit_card);
		if (total % 10 != 0)
		{
			printf("INVALID\n");
			return (0);
		}
		start_digits = get_start_digits(credit_card);
		if ((start_digits / 10 == 5) &&
			 (0 < start_digits % 10 && start_digits % 10 < 6))
			printf("MASTERCARD\n");
		else if ((start_digits / 10 == 3) &&
				 (start_digits % 10 == 4 || start_digits % 10 == 7))
			printf("AMEX\n");
		else if (start_digits / 10 == 4)
			printf("VISA\n");
		else
			printf("INVALID\n");
	}
	return (0);
}
