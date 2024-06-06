#pragma once

class Cell
{
public:
	Cell(bool bomb = false, bool flag = false, bool opened = false);
	~Cell();

	bool IsBomb();
	bool IsFlag();
	bool IsOpened();
	void AddBomb();
	void SwitchFlag();
	void Open();

	bool IsBomb() const;
	bool IsFlag() const;
	bool IsOpened() const;

	bool TryAddBomb();
	bool TrySwitchFlag();
	bool TryOpen();

private:
	bool bomb, flag, opened;
};
