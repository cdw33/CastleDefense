#ifndef UserInput_H
#define UserInput_H

class UserInput {
	private:

	public:
		UserInput()  { }
		~UserInput() { }
		
		string getName();
};

string UserInput::getName() {

	return "default entry";
}

#endif
