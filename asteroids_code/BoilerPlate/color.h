#pragma once

class color
{
private:
	float red;
	float green;
	float blue;
	float alpha;
public:
	color();
	color(float r, float g, float b, float aph);
	void setred(float target);
	void setgreen(float target);
	void setblue(float target);
	void setalpha(float target);
	void setall(float r, float g, float b, float aph);
	float getred();
	float getgreen();
	float getblue();
	float getalpha();

};
