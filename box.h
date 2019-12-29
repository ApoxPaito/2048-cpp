#ifndef BOX_H
#define BOX_X

class Box
{
private:
	int value;
	int newlyCombined;
public:
	Box();
	~Box();
	int GetValue() const;
	void SetValue(int);
	int IsNewlyCombined();
	void ChangeCombinedState();
};

#endif