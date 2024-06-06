#pragma once

class Cell
{
public:
	Cell(bool bomb = false, bool flag = false, bool opened = false);
	~Cell();

	bool HasBomb() const;
	bool HasFlag() const;
	bool IsOpened() const;
	bool TryAddBomb();
	bool TrySwitchFlag();
	bool TryOpen();

private:
	bool hasBomb, hasFlag, isOpened;
};
