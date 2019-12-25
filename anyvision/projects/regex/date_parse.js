

const DATE_REGEX = '(?<day>^[0-2]?[0-9]?|3[01])-(?<month>[01]?[0-9])-(?<year>\\d{4})';

function getDate(date) {

  const dateString = date;
  const matchRegex = new RegExp(DATE_REGEX);
  const match = matchRegex.exec(dateString);  if (match === null) {
    console.error('Incorrect date format');
    return;
  }

  let day = match.groups.day;
  let month = match.groups.month;
  let year = match.groups.year;

  console.log(
  `day  \t:\t${day}\nmonth\t:\t${month}\nyear\t:\t${year}`);
}

getDate('01-01-1111');
