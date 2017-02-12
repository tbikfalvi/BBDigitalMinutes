
-- -----------------------------------------------------------------------------------
USE digitalminutes_bb;
-- -----------------------------------------------------------------------------------

-- -----------------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS `organizations` (
  `organizationid` 					int(10) unsigned 		NOT NULL AUTO_INCREMENT,
  `organizationname` 	varchar(200) 			NOT NULL,
  `address` 			varchar(500) 			NOT NULL,
  `postaladdress` 		varchar(500) 			NOT NULL,
  `phone` 				varchar(200) 			NOT NULL,
  `mail` 				varchar(200) 			NOT NULL,
  `website` 			varchar(500) 			NOT NULL,
  `fieldname` 			varchar(200) 			NOT NULL,
  `fieldaddress` 		varchar(500) 			NOT NULL,
  `fieldphone` 			varchar(200) 			NOT NULL,
  `fieldseats` 			int(11) 				NOT NULL,
  `contactname` 		varchar(200) 			NOT NULL,
  `contactphone` 		varchar(200) 			NOT NULL,
  `contactmail` 		varchar(200) 			NOT NULL,
  PRIMARY KEY (`organizationid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- -----------------------------------------------------------------------------------
CREATE TABLE IF NOT EXISTS `teams` (
  `teamid` 				int(10) unsigned 		NOT NULL AUTO_INCREMENT,
  `organizationid` 		int(10) unsigned 		NOT NULL,
  `teamname` 			varchar(200) 			NOT NULL,
  `address` 			varchar(500) 			NOT NULL,
  `postaladdress` 		varchar(500) 			NOT NULL,
  `phone` 				varchar(200) 			NOT NULL,
  `mail` 				varchar(200) 			NOT NULL,
  `website` 			varchar(500) 			NOT NULL,
  PRIMARY KEY (`teamid`),
  FOREIGN KEY (`organizationid`) REFERENCES `organizations` (`organizationid`) ON UPDATE CASCADE ON DELETE RESTRICT
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
