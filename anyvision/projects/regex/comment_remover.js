function removeComments(scriptContent) {
  const SINGLE_LINE_COMMENT_REGEX = /(\/\/)(\n|[\w ]{1,})/g;
  const MULTI_LINE_COMMENT_REGEX = /\/\*[^*]*\*+(?:[^/*][^*]*\*+)*\//g;
  scriptContent = scriptContent.replace(SINGLE_LINE_COMMENT_REGEX, '');
  scriptContent = scriptContent.replace(MULTI_LINE_COMMENT_REGEX, '');
  console.log(scriptContent);
}

let scriptContent = `
//                     this is 

//sdfsdfsd
//sdfsdfsb                 df
/  /    sdfsdfsdf
//               s ldkfjsdk f                                        
//

fff
let a = 15;

/*
*a
*b
*c
*/

console.log('lalalalala');

/

/**/
/*what is*/`;

removeComments(scriptContent);

