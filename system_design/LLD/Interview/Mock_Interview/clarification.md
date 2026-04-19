design a split wise

- user create a group, multiple members
- all members can add transaction, select all the participants
- participants can clear debt
- no concurrency
- users should be able to see their balance (whether they owe or they lend)
- Notification


Entitites
- Group
- members
- User
- transaction
- transaction type (created, cleared)
- split type (equal, percentage..)

question
- Can any member join the group or only admin can add/remove the members ?


Design patterns

- Factory design (creating groups, members, user)
- Strategy design (split type)
- Oberserver deisgn pattern (notifications)
- State design pattern (transaction -> created -> cleared -> closed)

Secondary
- decorator (notification through multiple channels)



