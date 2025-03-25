document.addEventListener("DOMContentLoaded", function() {
  var languages = [
      ['ch', '中文'],
      ['en', 'English'],
  ];
  
  var h = '<select>';
  var url = location.href;
  var current_lang = url.match(/(?<=\/doc_).*?(?=\/html)/)[0] || languages[0][0];
  
  for (i = 0; i < languages.length; i++) {
      selected = ''
      if(current_lang === languages[i][0])
          selected = ' selected="selected"';
      h += '<option value="' + languages[i][0] + '"' + selected + '>' + languages[i][1] + '</option>';
  }
  h += '</select>';
  $("#projectlang")[0].innerHTML = h;
  $("#projectlang select")[0].addEventListener('change', function() {
      var v = $(this).children('option:selected').attr('value');
      var path = undefined;
      for (i = 0; i < languages.length; i++) {
          if(v === languages[i][0]) {
              path = languages[i][0];
              break;
          }
      }
      if (path) {
          var url = location.href;
          console.log(url);
          var current_lang = url.match(/(?<=\/doc_).*?(?=\/html)/)[0] || languages[0][0];
          console.log(current_lang);
          console.log(path);
          var new_url = url.replace("doc_" + current_lang, "doc_" + path);
          console.log(new_url);

          if (url != new_url)
                window.location.href = new_url;
      }
  });

  return current_lang;
});
