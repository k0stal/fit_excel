#include "spreadsheet.h"

CSpreadsheet::CSpreadsheet ():
    map() {}

CSpreadsheet::CSpreadsheet ( CSpreadsheet & arg ):
    map() {
    std::map<CPos, std::unique_ptr<ASTNode>> newMap;
    for ( const auto & cell : arg.map )
        map . emplace ( cell.first, cell.second->copy( std::pair(0, 0) ) );
}

CSpreadsheet::CSpreadsheet ( CSpreadsheet && arg ):
    map(std::move(arg.map)) {}

CSpreadsheet & CSpreadsheet::operator = ( const CSpreadsheet & arg ) {
    map.clear();
    for ( const auto & cell : arg.map )
        map . emplace ( cell.first, cell.second->copy( std::pair(0, 0) ));
    return *this;
}

bool CSpreadsheet::load(std::istream & is) {
    map.clear();
    char c;
    while (!is.fail()) {
        std::string cell = "";

        is.get(c);
        if (is.eof())
            return true;

        if (is.fail() || (!std::isalpha(c) && c != '$'))
            return false;
        cell += c;

        while (is.get(c) && std::isalpha(c) && !is.fail() && !is.eof())
            cell += c;

        if ((!isdigit(c) && c != '$') || is.fail() || is.eof())
            return false;
        cell += c;

        while (is.get(c) && isdigit(c) && !is.fail() && !is.eof())
            cell += c;

        if (c == '$')
            cell += c;
        else if (c != '-')
            return false;

        std::string sizeStr;
        while (is.get(c) && isdigit(c))
            sizeStr += c;

        if (c != '-')
            return false;

        int size = std::stoi(sizeStr);
        std::string value = "=";
        for (int i = 0; i < size; ++i) {
            if (is.fail() || !is.get(c))
                return false;
            value += c;
        }

        try {
            CPos pos(cell);
            if (!this->setCell(pos, value))
                return false;
        } catch (const std::exception &) {
            return false;
        }

        if (is.eof())
            return true;
    }

    return !is.fail();
}

bool CSpreadsheet::save ( std::ostream & os ) const {
    for ( const auto & cell : map ) {
        if ( os.fail() )
            return false;
        std::ostringstream oss;
        cell.second->print( oss );
        os << cell.first << "-" << oss.str().size() << "-" << oss.str();
    }

    if ( os.fail() )
        return false;

    return true;
}

bool CSpreadsheet::setCell ( CPos pos, std::string contents ) {
    ASTBuilder builder;
    try {
        parseExpression(contents, builder);
    } catch ( std::invalid_argument & e ) {
        return false;
    }

    std::unique_ptr<ASTNode> root;
    if (!builder.getLast(root))
        return false;
    auto it = map.find( pos );
    if ( it == map.end() ) 
        map . emplace ( pos, std::move(root));
    else
        it->second = std::move(root);
    return true;
}

CValue CSpreadsheet::getValue ( CPos pos ) {
    auto it = map.find(pos);
    if ( it != map.end() ) {
        std::set<CPos> visited = { pos };
        if ( it->second->detectCycle ( visited, this->map ) )
            return std::monostate{};
        return it->second->evaluate( map );
    }
    return std::monostate{};
}

void CSpreadsheet::copyRect ( CPos dst, CPos src, int w, int h ) {
    std::map<CPos, std::unique_ptr<ASTNode>> tmpMap;
    std::vector<CPos> srcPositions = {};
    rectIterationSize ( srcPositions, src, w, h );
    std::vector<CPos> dstPositions = {};
    rectIterationSize ( dstPositions, dst, w, h );
    for ( size_t i = 0; i < srcPositions.size(); i++ ) {
        auto it = map . find( srcPositions[i] );
        if ( it == map.end() )  
            continue;
        auto delta = dstPositions[i] - srcPositions[i];
        auto tmp = it->second->copy( delta );
        tmpMap . emplace ( dstPositions[i], std::move(tmp) );
    }
    for ( const auto & cell : tmpMap ) {
        auto it = map.find(cell.first); 
        if ( it == map.end() ) {
            auto tmp = cell.second->copy( std::pair(0, 0) );
            map . emplace ( cell.first, std::move(tmp));
        }   
        else {
            it->second = (cell.second->copy( std::pair(0, 0) ));
        }
    }
}
