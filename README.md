// --- ADMIN MAIN MENU ---
1. Personnel Management                   // Inheritance and polymorphism, Abstract base classes, Basic class design, Basic association
2. Race Management                        // Queue (linked list), Composition, Dependency
3. Team Management                        // Basic association, Qualified association, Association class
4. Vehicle Management                     // Basic class design, Composition, Association class, Qualified association
5. Performance & Stats                    // Operator overloading (member and non-member), Polymorphism, Basic class
6. System Info & Sample Data              // Abstract base/concrete classes, Integration testing, Best code/novel solution
7. Exit                                   



// --- PERSONNEL MANAGEMENT ---
1. Register New Driver                    // Basic class with constructors and accessors, Inheritance from abstract base class
2. View All Drivers                       // Polymorphism (viewing drivers through base class pointer/reference)
3. Search Driver by Name                  // Accessor methods, Basic string comparison
4. Register New Engineer                  // Basic class, Abstract base + inheritance (Engineer derived from Person)
5. View All Engineers                     // Polymorphism example (viewing multiple concrete derived types)
6. Search Engineer by Team                // Basic association (Engineer → Team)
7. Return to Main Menu                    // 


// --- RACE MANAGEMENT ---
1. Schedule New Race                      // Composition (using a Date object), Basic class with constructors
2. View Scheduled Races (Queue)           // Queue implemented via linked list
3. Enter Race Results                     // Composition (LapTime inside Race), Dependency (Race → Results)
4. View Race Results                      // Shows dependent relationship (Race object affects Leaderboard/Stats)
5. Delete Past Race from Queue            // Linked list manipulation (Queue)
6. Return to Main Menu                    // 


// --- TEAM MANAGEMENT ---
1. Create New Team                        // Basic class, Association with Drivers and Engineers
2. View All Teams                         // Association relationships displayed
3. Assign Driver to Team                  // Basic association (Team ↔ Driver)
4. Assign Engineer to Team                // Basic association (Team ↔ Engineer)
5. Search Team by Name                    // Qualified association (using team name as qualifier)
6. Return to Main Menu                    // 


// --- VEHICLE MANAGEMENT ---
1. Add New Vehicle                        // Basic class with accessors and constructors, Composition (engine specs)
2. View All Vehicles                      // Association class if vehicle is linked to driver
3. Assign Vehicle to Driver               // Association class (Vehicle ↔ Driver), Composition
4. Search Vehicle by Make or Driver       // Qualified association (search by attribute like make or driver name)
5. Return to Main Menu                    // 


// --- PERFORMANCE & STATS ---
1. View Lap Times (Reverse Order)         // Composition (LapTime), Recursive display, Optional sorting logic
2. View Leaderboard                       // Basic class, Operator overloading (non-member, for comparisons or sorting)
3. View Driver Performance Stats          // Operator overloading (as member function, e.g., compare two stats)
4. Compare Driver Stats                   // Polymorphism (different behavior for different driver objects), Overloading
5. Return to Main Menu                    // 


// --- SYSTEM INFO & SAMPLE DATA --- (Might get rid of this)
1. View Sample Driver & Engineer  
2. Load Sample Data  
3. Export Current Data to File  
4. View Application Info / Credits  
5. Return to Main Menu
