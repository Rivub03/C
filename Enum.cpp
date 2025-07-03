#include <iostream>
#include <iomanip>
using namespace std;

enum Day { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

// 2. ENUM WITH CUSTOM VALUES
enum Priority {
	LOW = 1,
	MEDIUM = 5,
	HIGH = 10,
	CRITICAL = 20
};

// 3. ENUM CLASS (C++11) - Strongly typed, scoped
enum class Color {
	RED,
	GREEN,
	BLUE,
	YELLOW
};

enum class Status {
	PENDING,
	PROCESSING,
	COMPLETED,
	FAILED
};

// 4. ENUM FOR STATE MACHINES
enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

// 5. ENUM FOR ERROR CODES
enum class ErrorCode {
	SUCCESS = 0,
	FILE_NOT_FOUND = 1,
	PERMISSION_DENIED = 2,
	NETWORK_ERROR = 3,
	INVALID_INPUT = 4
};

// 6. ENUM FOR DIRECTIONS (useful in games/graphics)
enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};


void displayDayName(Day d) {
	switch (d) {
	case MONDAY: cout << "Monday";
		break;
	case TUESDAY: cout << "Tuesday";
		break;
	case WEDNESDAY: cout << "Wednesday";
		break;
	case THURSDAY: cout << "Thursday";
		break;
	case FRIDAY: cout << "Friday";
	}
}
// Example 1: Without enums (bad practice)
void processTaskBad(int priority) {
	if (priority == 1) {
		cout << "Low priority task" << endl;
	}
	else if (priority == 5) {
		cout << "Medium priority task" << endl;
	}
	else if (priority == 10) {
		cout << "High priority task" << endl;
	}
	// What does priority = 7 mean? Unclear!
}

// Example 2: With enums (good practice)
void processTaskGood(Priority priority) {
	switch (priority) {
	case LOW:
		cout << "Processing low priority task" << endl;
		break;
	case MEDIUM:
		cout << "Processing medium priority task" << endl;
		break;
	case HIGH:
		cout << "Processing high priority task" << endl;
		break;
	case CRITICAL:
		cout << "URGENT: Processing critical task!" << endl;
		break;
	}
}

// Example 3: Game state management
void handleGameState(GameState state) {
	switch (state) {
	case GameState::MENU:
		cout << "Showing main menu" << endl;
		break;
	case GameState::PLAYING:
		cout << "Game is running" << endl;
		break;
	case GameState::PAUSED:
		cout << "Game is paused" << endl;
		break;
	case GameState::GAME_OVER:
		cout << "Game over! Final score displayed" << endl;
		break;
	}
}

// Example 4: Error handling with enums
ErrorCode openFile(const string& filename) {
	if (filename.empty()) {
		return ErrorCode::INVALID_INPUT;
	}
	if (filename == "nonexistent.txt") {
		return ErrorCode::FILE_NOT_FOUND;
	}
	if (filename == "protected.txt") {
		return ErrorCode::PERMISSION_DENIED;
	}
	return ErrorCode::SUCCESS;
}

void handleFileOperation(const string& filename) {
	ErrorCode result = openFile(filename);

	switch (result) {
	case ErrorCode::SUCCESS:
		cout << "File opened successfully!" << endl;
		break;
	case ErrorCode::FILE_NOT_FOUND:
		cout << "Error: File not found!" << endl;
		break;
	case ErrorCode::PERMISSION_DENIED:
		cout << "Error: Permission denied!" << endl;
		break;
	case ErrorCode::INVALID_INPUT:
		cout << "Error: Invalid filename!" << endl;
		break;
	default:
		cout << "Unknown error occurred!" << endl;
	}
}
// Example 6: Direction-based movement
void moveCharacter(Direction dir, int& x, int& y) {
	switch (dir) {
	case Direction::NORTH:
		y++;
		cout << "Moving North to (" << x << ", " << y << ")" << endl;
		break;
	case Direction::SOUTH:
		y--;
		cout << "Moving South to (" << x << ", " << y << ")" << endl;
		break;
	case Direction::EAST:
		x++;
		cout << "Moving East to (" << x << ", " << y << ")" << endl;
		break;
	case Direction::WEST:
		x--;
		cout << "Moving West to (" << x << ", " << y << ")" << endl;
		break;
	}
}
string dayToString(Day day) {
	switch (day) {
	case MONDAY: return "Monday";
	case TUESDAY: return "Tuesday";
	case WEDNESDAY: return "Wednesday";
	case THURSDAY: return "Thursday";
	case FRIDAY: return "Friday";
	case SATURDAY: return "Saturday";
	case SUNDAY: return "Sunday";
	default: return "Unknown";
	}
}

class TrafficLight {
private:
	Color currentColor;

public:
	TrafficLight() : currentColor(Color::RED) {}

	void changeLight() {
		switch (currentColor) {
		case Color::RED:
			currentColor = Color::GREEN;
			cout << "Light changed to GREEN - Go!" << endl;
			break;
		case Color::GREEN:
			currentColor = Color::YELLOW;
			cout << "Light changed to YELLOW - Caution!" << endl;
			break;
		case Color::YELLOW:
			currentColor = Color::RED;
			cout << "Light changed to RED - Stop!" << endl;
			break;
		default:
			break;
		}
	}

	Color getCurrentColor() const {
		return currentColor;
	}
};


int main() {

	int x;
	x = THURSDAY;
	cout << x << endl;
	Day workDay = FRIDAY;
	x = workDay;
	cout << x << endl;
	if (FRIDAY > MONDAY)
		cout << "Friday is greater than Monday. \n";
	if (MONDAY == 0)
		cout << "Monday is equal to zero.\n";

	const int NUM_DAYS = 5;
	double sales[NUM_DAYS];
	double total = 0.0;
	int index;
	for (index = MONDAY; index <= FRIDAY; index++) {
		cout << "Enter sales for the day " << index << ": ";
		cin >> sales[index];
		total += sales[index];
	}
	cout << "The total sales are $" << setprecision(2) << fixed << total << endl;

	Day day1, day2; // Defines two Day variables.
	day1 = TUESDAY; // Assign TUESDAY to day1.
	//day2 = day1 + 1; ERROR! This will not work!
	day2 = static_cast<Day>(day1 + 1); // This works.

	double costs[NUM_DAYS];
	costs[MONDAY] = 1525.0; // Stores 1525.0 in sales[0].
	costs[TUESDAY] = 1896.5; // Stores 1896.5 in sales[1].
	costs[WEDNESDAY] = 1975.63; // Stores 1975.63 in sales[2].
	costs[THURSDAY] = 1678.33; // Stores 1678.33 in sales[3].
	costs[FRIDAY] = 1498.52; // Stores 1498.52 in sales[4].

	string employees[NUM_DAYS];

	for (workDay = MONDAY; workDay <= FRIDAY; workDay = static_cast<Day>(workDay + 1)) {
		cout << "Enter the employee for the day: " << workDay << ": ";
		cin >> employees[workDay];
	}

	cout << "=== ENUM EXAMPLES IN C++ ===" << endl;

	// 1. Basic enum usage
	cout << "\n1. Basic Day Enum:" << endl;
	Day today = WEDNESDAY;
	cout << "Today is " << dayToString(today) << endl;
	cout << "Day value: " << today << endl;  // Prints 2

	// 2. Priority enum
	cout << "\n2. Priority Enum:" << endl;
	processTaskGood(HIGH);
	processTaskGood(CRITICAL);

	// 3. Enum class (scoped enums)
	cout << "\n3. Enum Class Examples:" << endl;
	Color favoriteColor = Color::BLUE;
	Status orderStatus = Status::PENDING;

	// Note: This won't compile - enum classes are scoped!
	// if (favoriteColor == Status::PENDING) // ERROR!

	cout << "Order status is pending" << endl;

	// 4. Game state management
	cout << "\n4. Game State Management:" << endl;
	GameState gameState = GameState::MENU;
	handleGameState(gameState);

	gameState = GameState::PLAYING;
	handleGameState(gameState);

	// 5. Error handling
	cout << "\n5. Error Handling:" << endl;
	handleFileOperation("test.txt");
	handleFileOperation("nonexistent.txt");
	handleFileOperation("");

	// 6. Traffic light example
	cout << "\n6. Traffic Light Example:" << endl;
	TrafficLight light;
	light.changeLight();
	light.changeLight();
	light.changeLight();

	// 7. Character movement
	cout << "\n7. Character Movement:" << endl;
	int playerX = 0, playerY = 0;
	moveCharacter(Direction::NORTH, playerX, playerY);
	moveCharacter(Direction::EAST, playerX, playerY);
	moveCharacter(Direction::SOUTH, playerX, playerY);
	moveCharacter(Direction::WEST, playerX, playerY);

	// 8. Demonstrating enum vs enum class
	cout << "\n8. Enum vs Enum Class:" << endl;

	// Regular enum - can be implicitly converted to int
	Priority taskPriority = HIGH;
	int priorityValue = taskPriority;  // This works
	cout << "Priority value: " << priorityValue << endl;

	// Enum class - cannot be implicitly converted
	Color wallColor = Color::RED;
	// int colorValue = wallColor;  // This would cause compilation error!
	int colorValue = static_cast<int>(wallColor);  // Need explicit cast
	cout << "Color value: " << colorValue << endl;


	return 0;
}


