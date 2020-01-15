const loremString = 'sollicitudin ligula ultrices primis odio pharetra proin vitae at blandit ac donec ad amet morbi commodo lacus vestibulum wisi wisi non lobortis non luctus risus arcu eu ac inceptos est sit orci nec posuere vel consectetuer voluptas eu malesuada quis nibh duis urna cras leo habitant velit eu proin aenean eros habitant viverra eget erat porttitor vulputate mi et aliquam vestibulum nisi faucibus sed duis amet cum ante ut metus nec vestibulum risus risus in amet aut eleifend velit ipsum gravida dui lorem libero nec libero a malesuada elit ut maecenas lorem aliquam scelerisque ac elit pulvinar interdum nec et vitae blandit donec lacus scelerisque est enim morbi euismod habitasse ante nunc lacinia amet amet cillum lacinia sit quam adipiscing lacus blandit blandit condimentum ut nullam sagittis dictum rhoncus in a tellus pellentesque luctus elit aliquam sit nec quam nunc mattis turpis neque semper nec nibh sodales ante congue enim pretium pede nam dicta a turpis dolor placerat dignissim ipsum neque aliquam tortor sapien magna dui eu vel neque pede ultricies magna donec id libero integer justo sit pede sagittis non cum eleifend enim quam pede dui in sed semper mus quam vestibulum ut lacus at mattis velit ipsum amet massa quisque quis blandit sed faucibus pede amet scelerisque ut hendrerit ac mauris ex vitae varius mauris porttitor eu consectetuer in felis vel vivamus sed lacus aenean elit lacus augue elit auctor fermentum id mauris suspendisse integer proin ornare ac sed malesuada mollis in sagittis odio molestie vel proin risus vehicula pellentesque feugiat viverra congue fusce ac imperdiet ipsum sed lorem luctus quis in nulla donec vitae integer nec id turpis ante eleifend feugiat tortor nulla nec cubilia sem rhoncus tempor donec eget convallis sit sed diam nonummy sed lobortis est diam amet fringilla dolor turpis non sed ut non';
const lorem = loremString.split(' ');

function getRandomInt (min, max) {
  return Math.floor(Math.random() * (max - min)) + min; //The maximum is exclusive and the minimum is inclusive
};

function generatePostsInLocalStorage() {
  let numWordsInTitle = getRandomInt(1, 300);
  let title = '';
  let content = ''
  for (let i = 0; i < numWordsInTitle; i += 1) {
    title = title + ' ' + lorem[i];
  }
  ;

  let numWordsInContent = getRandomInt(1, 300);
  for (let i = 0; i < numWordsInContent; i += 1) {
    content = content + ' ' + lorem[i];
  }
  ;
}


