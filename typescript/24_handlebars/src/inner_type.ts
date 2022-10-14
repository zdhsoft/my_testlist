type weekDay = 'Mon' | 'Tue' | 'Wed' | 'Thu' | 'Fri';
type Day = weekDay | 'Sat' | 'Sun';

const nextDay: { [k in weekDay]: Day } = {
    Mon: 'Sat',
    Tue: 'Sun',
};
