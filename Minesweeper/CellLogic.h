#pragma once

class CellLogic
{
public:
	CellLogic(bool bomb = false, bool flag = false, bool opened = false);
	~CellLogic();

	bool HasBomb() const;
	bool HasFlag() const;
	bool IsOpened() const;
	bool TryAddBomb();
	bool TrySwitchFlag();
	bool TryOpen();

private:
	bool isBomb; 
	bool isFlag;
	bool isOpened;
};
