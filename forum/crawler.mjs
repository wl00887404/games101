import fs from 'fs';
import axios from 'axios';
import { load } from 'cheerio';

const totalPage = 66;

const getUrl = page => {
  const url = 'https://games-cn.org/forums/forum/graphics-intro/';
  if (page === 1) return url;

  return `${url}page/${page}/`;
};

const fetchHtml = () => {
  for (let page = 1; page <= totalPage; page++) {
    const url = getUrl(page);
    axios.get(url).then(({ data }) => {
      fs.writeFileSync(`./cache/${page}.html`, data);
    });
  }
};

const parseHtml = () => {
  const posts = [];
  for (let page = 1; page <= totalPage; page++) {
    const html = fs.readFileSync(`./cache/${page}.html`);

    const $ = load(html);
    $('.bbp-body ul').each((_, ul) => {
      const post = {
        title: $(ul).find('.bbp-topic-permalink').text(),
        link: $(ul).find('.bbp-topic-permalink').attr('href'),
        author: $(ul).find('.bbp-topic-title .bbp-author-name').text(),
        lastUpdate: $(ul).find('.bbp-topic-freshness > a').text(),
      };
      posts.push(post);
    });
  }

  const blackList = [
    'litianzhen01',
    'yrurirddd',
    '鼓风',
    'saraclover',
    'wellos',
    'Fersalio',
    'cbssportscomrokucode',
    'desktop',
    'Atish01',
    'Melvinburk',
    'celectstudios',
    'Stella Potter',
    'Angelia22',
    'Diane22',
    'christicouch',
    'jenny',
    'Ronald Mane',
    'Emilylowes',
    'MeadeDorianx',
    'Shirley',
    'OlenaDemchuk',
    'MeadeDorianx',
    'greatideas',
    'Sara Palm',
    'lockpickmallcom',
    'Maxwell',
    'blessingsfromafrica',
    'BeauDiego',
    'Buyd4items',
    'Chair',
    'Chair',
    'Greetingfromafrica',
    'HerMuller',
    'MeadeDorian',
  ];
  const filtered = posts.filter(post => !blackList.includes(post.author));

  fs.writeFileSync('../docs/posts.zh-ch.json', JSON.stringify(filtered, null, 2));
};

parseHtml();
