class ratNum//class for a rational number
{
public:
	ratNum();				 //Initialize ratNum to be 0/1
	~ratNum();				 //Destructor
	int getnum() const;		 //Return the value of num 
	int getdenom() const;	 //Return the value of denom
	void setnum(int *n);	 //Set the value of num
	void setdenom(int *dn);	 //Set the value of denom
	void disp() const;		 //Display the user input rational number
	int hcf(ratNum *p);		 //Access the other rational number's denominator and compute their HCF
	int lcm(ratNum *p);		 //Access the other rational number's denominator and compute their LCM
	void add(ratNum* p);	 //Addition of two rational number by using LCM
	void power(int n);		 //Compute the rational number to the power of n and simplify it using HCF

private:
	int num, denom;		//num is numerator , denom is positive denominator
};
