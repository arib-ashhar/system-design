 - System shouel manage multiple bookings
 - Each User can browse and select multiple seats
 - A theatre can have multiple screens, each screen should have shows in slots
 - central system to manage bookings, add shows remove shows, add screens, remove screens
 - there can be multiple locations

Booking
 - User selects show, select the seats, go to payment and confirm booking
 - should handle double booking, concurrent booking

How should we handle concurrent booking ?
What happens if user goes to payment page and doesn't confirm booking ?
IS there any time constraint for booking ?

 - temp seat locking
 - freeze seat for 5 minutes, if payment is not confirmed release the seat


Entities:
 - Theatre
 - Screens
 - Shows
 - Movies
 - Seat
 - Locations
 - User

Enums:
 - BookingStatus
 - SeatCategory


Approach
 - IN a prod codebase. I would use Repository design pattern.
 - Controller -> ServiceLayer -> DB actions
 - Dues to time constraint I'll write skip the controller->service layer

Design Patterns
 - Factory Design Pattern
    - seats
    - THeatre
    - screen
    - shows
 - Strategy Design Pattern
    - Payment types
    - Seat Locking
 - Observer design pattern
    - Notify the users
 - Decorator design pattern
    - If we want to add multiple channels of notification (Whatsapp, SMS, email)


Dependency INjection
 - Service layer can inject different providers using constructors
    ex: bookingService can inject seatLockProvider
